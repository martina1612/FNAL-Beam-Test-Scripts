#Environment Setting for Lxplus
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

 
## How to Run:
First you need to run the **TurboSoftware** to get the root file from EventBuilder step (root file should be of type CRC\*.root). Then there are two steps in the alignment framework. First step is to get the text file with hit information. Then, in next step takes this text file with hit info and tries to align the detector.

### Step 1: Get the text file to process in step 2.
	./RunAiwuTextFile.sh <Initial Run Number>  <Final Run Number>

You may need to modify the path of input root files. Also, there are two variables named **EfficiencyType** and **TrkOnly**. Need to choose the values of this variable in code. Description of these variables given in code itself.

### Step 2: Alignment part
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> No 1		# Will create text file with tracker info only
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> LC1 1		# Will create text file with tracker & one GE11
	./RunAiwuSoftware.sh <Initial Run Number>  <Final Run Number> No 0		# Run the alignment code
