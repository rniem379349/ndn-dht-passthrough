import matplotlib.pyplot as plt


def get_trace_parameters(input_line):
  result = []
  result = input_line.split()
  return result

def construct_trace_dict(input_line, param_names):
  result = {}
  input_line = input_line.split()
  for i in range(len(param_names)):
    result[param_names[i]] = input_line[i]
  return result

def getMetricDictFromTxtFile(metricsFile):
  metricsFile = open(metricsFile, 'r')
  trace_lines = metricsFile.readlines()
  metricsFile.close()
  return trace_lines

def mean(arr):
  sum = 0
  for item in arr:
    sum += float(item)
  return sum/len(arr)



# Test with sample app delay trace file
metricId = 0
metrics = {}

metricsArr = getMetricDictFromTxtFile("app-delays-trace2.txt")
param_arr = get_trace_parameters(metricsArr[0])

for line in metricsArr[1::]:
  metrics[metricId] = construct_trace_dict(line, param_arr)
  metricId += 1

lastDelayValsLeaf1 = []
fullDelayValsLeaf1 = []
lastDelayValsLeaf2 = []
fullDelayValsLeaf2 = []
lastDelayValsLeaf3 = []
fullDelayValsLeaf3 = []

for line in metrics:
  if(metrics[line]["Type"] == "LastDelay"):
    if (metrics[line]["Node"] == "leaf-1"):
      lastDelayValsLeaf1.append(metrics[line]["DelayS"])
    elif (metrics[line]["Node"] == "leaf-2"):
      lastDelayValsLeaf2.append(metrics[line]["DelayS"])
    elif (metrics[line]["Node"] == "leaf-3"):
      lastDelayValsLeaf3.append(metrics[line]["DelayS"])
  elif(metrics[line]["Type"] == "FullDelay"):
    if (metrics[line]["Node"] == "leaf-1"):
      fullDelayValsLeaf1.append(metrics[line]["DelayS"])
    elif (metrics[line]["Node"] == "leaf-2"):
      fullDelayValsLeaf2.append(metrics[line]["DelayS"])
    elif (metrics[line]["Node"] == "leaf-3"):
      fullDelayValsLeaf3.append(metrics[line]["DelayS"])


lastDelayValsLeaf1Mean = mean(lastDelayValsLeaf1)
lastDelayValsLeaf2Mean = mean(lastDelayValsLeaf2)
lastDelayValsLeaf3Mean = mean(lastDelayValsLeaf3)

lastDelaysAverages = [lastDelayValsLeaf1Mean, lastDelayValsLeaf2Mean, lastDelayValsLeaf3Mean]

leafNames = ['leaf-1', 'leaf-2', 'leaf-3']
y_pos = range(len(leafNames))
plt.bar(y_pos, lastDelaysAverages, align='center', alpha=0.5, color='red')
plt.xticks(y_pos, leafNames)
plt.ylabel('Delay')
plt.title('Average delay times')
plt.show()