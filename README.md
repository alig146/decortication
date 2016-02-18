# Decortication

A python package specific to my fatjet study.

## Datasets
Dataset information is stored in `resources/samples.yaml`. The format is a dictionary of dictionaries. The outer dictionary is keyed by the dataset *category*; the inner dictionary is keyed by the dataset *process* and has a list of dictionaries corresponding to datasets representing each unique *subprocesses*. These dataset dictionaries have the following keys:
* `name`: The official dataset name (**unique**)
* `subprocess`: The subprocess name. If not present, the subprocess is the same as the process. (**unique**)
* `m`, `pts`, `hts`: Identifying parameters for the subprocess
* `sigma`: The cross section of the subprocess
* `generation`: The dataset *generation* ("spring15", etc.)
* `n`: The number of events in the dataset
* `miniaod`: The MiniAOD path of the dataset
* `jets`: The jets path of the dataset
