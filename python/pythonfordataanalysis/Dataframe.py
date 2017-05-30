data = {'state':['Ohio','Ohio','Ohio','Nevada','Nevada'],'year':[2000, 2001, 2002, 2001, 2002], 'pop':[1.5, 1.7, 3.6, 2.4, 2.9]}
from pandas import DataFrame
import pandas as df
frame = DataFrame(data)
frame
DataFrame(data, columns=['year','state','pop'])
data
frame
frame2 = DataFrame(data, columns=['year','state','pop','debt'],index=['one','two','three','four','five'])
frame2
frame2.columns
frame2['state']
frame2['pop']
frame2['debt']
frame2.year
frame2['year']
frame2.ix['three']
frame2.ix['two']
frame2['debt']=16.4
frame2['debt']=16.5
frame2
frame2['debt']=np.arrange(5.)
import numpy as np
frame2['debt']=np.arrange(5.)
frame2['debt']=np.arange(5.)
frame2
val = Series([-1.2, -1.5, -1.7], index=['two','four','five'])
val = Series([-1.2, -1.5, -1.7], index=['two','four','five'])
from pandas import Series
val = Series([-1.2, -1.5, -1.7], index=['two','four','five'])
val
frame2['debt']=val
frame2
frame2['eastern'] = frame2.state == 'Ohio'
frame2
del frame2['eastern']
frame2
frame2.columns
frame2['eastern'] = frame2.state == 'Ohio'
frame2.columns
del frame2['eastern']
frame2.columns
pop = {'Nevada':{2001: 2.4, 2002:2.9}, 'Ohio':{2000:1.5, 2001:1.7, 2002:3.6}}
pop
frame3 = DataFrame(pop)
frame3
frame2
frame3.T
frame2.T
frame3.T
frame3
DataFrame(pop, index=[2001,2002,2003])
pdata = {'Ohio':frame3['Ohio'][:-1], 'Nevada':frame3['Nevada'][:2]}
pdata
DataFrame(pdata)
frame3.index.name='year'
frame3.column.name='state'
frame3.columns.name='state'
frame3
frame3.values
frame3.index
frame2.values
obj = Series(range(3), index=['a','b','c'])
obj
obj.index
index[1:]
index[1:]
index
index=obj.index
index[1:]
index[1] = 'd'
index = pd.Index(np.arange(3))
import pandas as pd
index = pd.Index(np.arange(3))
obj2
obj2=Series([1.5,-2.5,0], index=index)
obj2.index is index
index
obj2
frame3
'Ohio' in frame3.columns
2003 in frame3.columns
frame3.columns
obj = Series([4.5, 7.2, -5.3, 3.6], index=['d','b','a','c'])
obj
obj2 = obj.reindex(['a','b','c','d','e'])
obj2
