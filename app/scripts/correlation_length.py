import anesthetic as ns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os



#path = "/rds/user/bd418/hpc-work/correlation"
path = "/Users/borisdeletic/CLionProjects/CHMC-Nested-Sampling/cmake-build-release/app/phi4/correlation"

R = 512

file_list = sorted(os.listdir(path))
files_searched = []

print(file_list)
correlation_samples = pd.DataFrame()
mags = pd.DataFrame()

def correlationLength(correlations):

    log_correlations = np.log(np.abs(correlations[:len(correlations)]))

    print(log_correlations)

    xis = []
    kappas = []
    fig, ax = plt.subplots()
    for kappa in log_correlations.columns.values:
        m,b = np.polyfit(log_correlations.index.values, log_correlations[kappa], 1)

        xi = -1 / m

        xis.append(xi)
        kappas.append(kappa)
        ax.plot(log_correlations[kappa], label="k={:.5f}, xi={:.3f}".format(kappa, xi))
    #    ax.plot(kappa, , label="k={:.5f}, xi={:.3f}".format(kappa, xi))

    #ax.scatter(kappas, xis)
    ax.legend(loc="upper right")

   # ax.figure.savefig('log_corr.png')



fig, ax = plt.subplots()
for file in file_list:
    fname = file[:22]

    if fname in files_searched or fname == '.DS_Store':
        continue
    else:
        files_searched.append(fname)

    kappa = float(fname.split("_")[1])
    l = fname.split("_")[2]

    chains = os.path.join(path, fname)
    samples = ns.read_chains(chains)
    posterior = samples.posterior_points()

    mean_mag = abs(posterior['mag']).mean()

    print("meanmag = {}".format(mean_mag))
    correlations = []
    for r in range(1, R):
        c_key = "c_{}".format(r)

        mean_correlation = posterior[c_key].mean() - mean_mag*mean_mag
       # print(c_key)
        #print(mean_correlation)
        correlations.append(mean_correlation)

    correlations /= posterior["c_0"].mean()
    correlation_samples[kappa] = correlations
    mags[kappa] = mean_mag

#print(correlation_samples[:32])

correlation_samples.to_csv("correlation_data.csv", index=False)

correlationLength(correlation_samples)

for kappa, correlation in correlation_samples.iterrows():
    ax.plot(correlation[kappa], label="k={:.5f}, m={:.2f}".format(kappa, mags[kappa]))


ax.legend(loc="upper right")
plt.show()
#ax.figure.savefig('correlations.png')



