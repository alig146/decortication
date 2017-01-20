# Decortication

A python package specific to my [https://github.com/elliot-hughes/fatjet_analysis](fatjet analysis).

## Installation
1. Download the package with `git clone git@github.com:elliot-hughes/decortication.git`.

## Datasets
Dataset information is stored in `resources/samples.yaml`. The format is a dictionary of dictionaries. The outer dictionary is keyed by the dataset *category*; the inner dictionary is keyed by the dataset *process* and has a list of dictionaries corresponding to each unique *subprocesses*. These subprocess dictionaries are called *samples* and each contain a list of corresponding *miniaod* dictionaries. The keys of these sample and miniaod dictionaries are defined in `resources/database.yaml`.

### Primary keys
Shared by samples and miniaods:

* `category`: A tag indicating the general sort of dataset (e.g., jetht)
* `process`: A tag describing the specific dataset. This key is not unique, since multiple samples may be part of the same dataset.
* `subprocess`: A tag describing the particular sample. If not specified, the subprocess is the same as the process. (**unique**)
* `name`: The official dataset name (**unique**)
* `data`: A binary flag for whether the dataset is data (`1`) or MC (`0`)
* [...]

### Sample keys
* `m`, `pts`, `hts` (`parameterx`): Identies parameters of the subprocess
* `sigma`: The cross section of the subprocess
* [...]

### Miniaod keys
* `generation`: The MiniAOD *generation* (e.g., `spring15`)
* `n`: The number of events in the MiniAOD files
* [...]
