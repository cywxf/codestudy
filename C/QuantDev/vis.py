import sys
import os
from pandas import DataFrame
import pandas as pd
import matplotlib.pyplot as plt

#matplotlib.use('Agg')
filename = sys.argv[1]
df = pd.read_csv(filename, sep=",")
#df['Time'] = pd.to_datetime(df['Time'])
df.plot(x='Time', y='Price', style='o')
plt.scatter(df['Time'], df['Price'])
plt.show()
plt.ion()
print(df[:10])

