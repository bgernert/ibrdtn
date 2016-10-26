#
# This script generates all missing files
#

$ErrorActionPreference = "Stop"

$localDir = Split-Path $MyInvocation.MyCommand.Path
$subDirs = @("ibrcommon", "ibrdtn", "daemon", "tools")

# Switch to script dir
cd $localDir

# Create a link to ibrcommon
if((Test-Path ibrcommon) -eq $false) {
    New-Item -ItemType Junction -Value ..\ibrcommon -Name ibrcommon | Out-Null
}

foreach($dir in $subDirs) {
    "## enter directory $dir ##"
    cd $localDir\$dir

    # create m4 directory
    if((Test-Path m4) -eq $false) {
        New-Item -ItemType Directory -Path m4 | Out-Null
    }

    if((Test-Path autogen.ps1) -eq $true) {
        "## run autogen.ps1 script ##"
        Invoke-Expression ((Split-Path $MyInvocation.InvocationName) + "\autogen.ps1" + " $args")
    }
}

"## run autoreconf in the main directory ##"
cd $localDir

# create m4 directory
if((Test-Path m4) -eq $false) {
    New-Item -ItemType Directory -Path m4 | Out-Null
}

# create version file
Invoke-Expression ((Split-Path $MyInvocation.InvocationName) + "\mkversion.ps1" + " $args")

# run autotools
autoreconf -i