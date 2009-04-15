
class CompositeModel(FeedModel):
    def __init__(self, models, sortby):
        self.models = models
        self.sortby = sortby
    def type(self):
        return "CompositeModel"
    def items():
        tmp = []
        for model in models:
            tmp += model.items()
        tmp.sort(lambda x,y:cmp(x.date, y.date))
        return tmp
