def index(keys,values,match):
    return {i : [x for x in values if match(i,x)] for i in keys}