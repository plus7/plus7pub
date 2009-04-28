#import <stdio.h>
#import <objc/Object.h>

@interface TestClass : Object
- (void)getMessage;
@end

@implementation TestClass
- (void)getMessage
{
	printf("hello obj-c\n");
}
@end

int main(int argc, char* argv[])
{
	id obj = [TestClass alloc];
	[obj getMessage];
	return 0;
}