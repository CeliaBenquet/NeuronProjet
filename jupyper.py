

import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes.gdf')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
pl.scatter(data1[0],data1[1],alpha=0.8, edgecolors='none', s=4);
pl.ylabel("Neurons index")
pl.xlabel("Time (ms)")
pl.show();

n, bins, patches = pl.hist(0.1*data1[0], 50, normed=0, alpha=0.75)
pl.ylabel("Number of spikes")
pl.xlabel("Time (ms)")
pl.show();
