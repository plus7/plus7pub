/*
 * lex.c
 *
 * This file is a part of Lexical Analyzer for weash.
 *
 * Copyright 2007 NOSE takafumi <ahya365@gmail.com>
 *
 * Licensed under the Common Public License version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * A copy of the License is available at
 * http://www.opensource.org/licenses/cpl1.0.txt
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.
 * 
 */
#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "linkedlist.h"
/*
 エスケープシーケンスと文字列連結
に並べた文字は、シェルスクリプトでは特殊な文字として扱われ、そのままでは普通の文字として扱ってくれません。
; & ( ) | ^ < > ? * [ ] $ ` " ' { } [TAB] [SPACE]

これらを普通の文字として扱うためには、適当にエスケープする必要があります。

特殊文字をエスケープするには次の3つが使われます。

バックスラッシュ( \ )により一文字エスケープ
シングルクォーテーション( ' )で囲む
ダブルクォーテーション( " )で囲む

バックスラッシュにより一文字エスケープ
バックスラッシュ ( \ ) の直後の特殊文字は普通の文字として扱われます。
シングルクォーテーションで囲む
シングルクォーテーション ( ' ) で囲まれた中の特殊文字はすべて普通の文字として扱われます。

ダブルクォーテーション ( " ) で囲む
ダブルクォーテーションで囲まれた中の特殊文字は $ ` \ を除いてすべて普通の文字として扱われます。
つまり、ダブルクォーテーション中では 変数、コマンド置換 が行われます。
これが、シングルとダブルのクォーテーションの意味の違いです。 
 * */
/*
 * 文法	意味
< file	標準入力先をfileに変更する。
> file	標準出力先をfileに変更する。fileがすでに存在していた場合上書きされる。
>> file	標準出力先をfileに変更する。fileがすでに存在していた場合追加される。
 * */
/*
 * パイプラインによる標準入出力の接続はリダイレクトに先立って行われる
 * 
 * トークンのリスト
 * 
 * シェルへの指令
 * 		
 * 個々のコマンド
 * 		コマンド名 SP+ コマンドライン引数
 * コマンド名
 * 		ファイル名の正規表現と一緒
 * コマンドライン引数
 * 		エスケープされた文字列　または　コマンド置換された文字列　または　シングルクォートによるエスケープ
 * リダイレクト
 * 		エスケープされていない<、>
 * パイプ
 * 		エスケープされていない|
 * コマンド置換 `...`
 * 特殊文字のエスケープ '...'
 * ※　変数はサポートしない　※
 * 
 * ■サポート
 * |：パイプ
 * < >：リダイレクト
 * `：バッククォート　コマンド置換 
 * '：シングルクォート
 * \：一文字エスケープ
 * 
 * ■非サポート
 * ;：逐次実行
 * &：&&でAND
 * ( ) ：$と組み合わせてコマンド置換
 * ||：OR
 * ^：?
 * ? *：ワイルドカード 
 * [ ]：ブラケット 
 * $：変数 
 * "：ダブルクォート
 * { }：ブレース展開 
 * [TAB]：補完 
 * [SPACE]：区切り
 * */


int lex(char *line, struct TokenList *h){
	int i = 0;
	struct sstr buff;
	int mode = 0; //0:Normal 1:Quote 2:DQuote
	
	if(line==NULL) return -1; //何も入力されていない
	
	int len = strlen(line);
	initsstr(&buff);
	for(;;){
		//printf("char:%c i=%d\n", line[i], i);
		if(line[i]=='\0'){
			if(mode==1||mode==2) {break;} //途中で途切れているのでおかしい
			else {
				//printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
				break;}
		}
		
		if(mode==0){ //ノーマル
			for(;i<len;i++){
				if(line[i]==' ' || line[i]=='\t' || line[i]=='\n'){ //まず最初の空白は無視
					printsstr(&buff);
					insert_item(h, WORD, buff.data);
					clearsstr(&buff);
					continue;
				}
				else break;
			}
			//この時点で、最初の文字が空白以外であることが保証される
			
			if(line[i]=='\''){
				mode = 1;
				i++;
				continue;
			}
			else if(line[i]=='"')
			{
				mode = 2;
				i++;
				continue;
			}
			else if(line[i]=='<')
			{
				printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
				insert_item(h, REDIR_IN, "");
				//printf("Input\n");
			}
			else if(line[i]=='>')
			{
				if(line[i+1]=='>'){
					printsstr(&buff);
					insert_item(h, WORD, buff.data);
					insert_item(h, REDIR_ADD, "");
					clearsstr(&buff);
					//printf("Add\n");
					i++;
				}
				else{
					printsstr(&buff);
					insert_item(h, WORD, buff.data);
					clearsstr(&buff);
					//printf("Output\n");
					insert_item(h, REDIR_OUT, "");
				}
			}
			else if(line[i]=='|')
			{
				printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
				insert_item(h, PIPE, "");
				//printf("Pipe\n");
			}
			else if(line[i]=='&')
			{
				printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
				insert_item(h, AMP, "");
				//printf("Amp\n");
			}
			else if(line[i]=='\\'){
				if(line[i+1]!='\0'){
					i++;
					addchar(&buff, line[i]);
				}
			}
			else 
			{
				//printf("addchar\n");
				addchar(&buff, line[i]);
			}
		}
		else if(mode==1)
		{
			if(line[i]=='\\'){
				if(line[i+1]!='\0'){
					i++;
					addchar(&buff, line[i]);
				}
			}
			else if(line[i]=='\'')
			{
				mode=0;
				printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
			}
			else 
			{
				addchar(&buff, line[i]);
			}
		}
		else 
		{
			if(line[i]=='\\'){
				if(line[i+1]!='\0'){
					i++;
					addchar(&buff, line[i]);
				}
			}
			else if(line[i]=='"')
			{
				mode=0;
				printsstr(&buff);
				insert_item(h, WORD, buff.data);
				clearsstr(&buff);
			}
			else 
			{
				addchar(&buff, line[i]);
			}
		}
		//printf("i++\n");
		i=i+1;
	}
	//コマンドライン最初のトークンはOTHER、QUOTE、DQUOTE。
	//ワード [SP] OTHER|QUITE|DQUOTE
	//リダイレクト（入力）[SP] LT [SP] word
	//リダイレクト（出力）[SP] GT [SP] word
	//バックグラウンド [SP] AMP
	//パイプ [SP] PIPE
	//printf("finished. i=%d\n",i);
	purgesstr(&buff);
}
