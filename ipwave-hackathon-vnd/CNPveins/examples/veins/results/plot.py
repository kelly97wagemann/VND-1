import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd
import glob
import os
from cycler import cycler

mpl.rcParams['axes.prop_cycle'] = cycler(color='bgrcmyk')
plt.rc('font', family='serif')

def sca(scava_path):
    paths = glob.glob("./*.sca")
    for path in paths:
        flux = path.split("#22")[1].split("#_")[0]
        vel = path.split("#22")[1].split("#_")[1].split("Highway")[0]
        cmd = "{0} x '{1}' -o {2}_{3}.csv".format(scava_path, path, flux, vel)
        os.system(cmd)

def messages(path):
    df = pd.read_csv(path)
    filter_nan1 = df[df['module'].notnull()]
    filter_nan2 = filter_nan1[filter_nan1['value'].notnull()]
    #nodes = filter_nan2[filter_nan2['module'].str.contains(r"node\[")]
    nodes = filter_nan2
    sentSignals = nodes[nodes['name'].str.contains("numSentSignal")]
    return sentSignals['value'].sum()

def plot():
    paths = glob.glob("./*.csv")
    data_dict = {'99':([], []), '131':([], []), '174':([], [])}
    for path in paths:
        flux = path.split("./")[1].split("_")[0]
        velocity = path.split("./")[1].split("_")[1].split(".")[0]
        data_dict[str(flux)][0].append(int(velocity))
        #print(flux + " " + velocity)
        data_dict[str(flux)][1].append(messages(path))
    return data_dict

sca("/home/danilo/Downloads/omnetpp-5.4.1/bin/scavetool")
results = plot()

velocities, message_number = results['99']
X99, y99 = zip(*sorted(zip(velocities, message_number)))

plt.plot(X99, y99, marker="o", label="Slight")

velocities, message_number = results['131']
X131, y131 = zip(*sorted(zip(velocities, message_number)))
plt.plot(X131, y131, marker="s", label="Moderate")

velocities, message_number = results['174']
X174, y174 = zip(*sorted(zip(velocities, message_number)))
plt.plot(X174, y174, marker="^", label="Severe")

plt.xlabel("Maximum Velocity [m/s]")
plt.ylabel("Number of Messages")
plt.legend(title="Traffic Density")
plt.title("Neighbor Discovery messages versus maximum velocity")
plt.savefig("message_number_ND.png", dpi=600)
plt.show()




"""
df = pd.read_csv("two.csv")
#print(df.dtypes)
#print(df['module'].unique())

filter_nan1 = df[df['module'].notnull()]
filter_nan2 = filter_nan1[filter_nan1['value'].notnull()]

nd = filter_nan2[filter_nan2['module'].str.contains("ipv6.neighbourDiscovery")]
dropping = nd.drop(columns=['run', 'type','sumweights', 'attrname', 'attrvalue', 'stddev', 'count', 'mean', 'min', 'max'])
dropping["module"] = dropping.module.str.split('.', expand=True)[1]

#print(dropping['name'].unique())
#print(dropping)

node1 = dropping[dropping['module'].str.contains(r"node\[1\]")]
#print(node1)

"""
