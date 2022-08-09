# Input conversion

## Supported formats

At present the framework supports model input in two file formats:

 - **Yaml** (for ASCII input)
 - **NetCDF** (for binary input)

For a number of other simulations systems, scripts are available to convert existing model input to the currently-supported formats.
For now, this is only supported for the Yaml file format.

The (Python) conversion scripts can be found in the scripts/converters folder: 

 - D-Flow Flexible Mesh: [scripts/converters/convertDflowfmToYaml.py](../scripts/converters/convertDflowfmToYaml.py)
 - SFINCS: [scripts/converters/convertSfincsToYaml.py](../scripts/converters/convertSfincsToYaml.py)
 
## Usage

The scripts can be used by executing the script with the main input file (full path) as command-line argument, e.g.:

- D-Flow Flexible Mesh: `python convertDflowfmToYaml.py data/input/fm_input.mdu`
- SFINCS: `python convertSfincsToYaml.py data/input/sfincs.inp`

Possible nested/referenced files in the main input file are parsed and converted automatically.
It is to be noted that only a (basic) subset of the full input files for the aforementioned systems is currently supported.


