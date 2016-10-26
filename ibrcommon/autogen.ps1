$ErrorActionPreference = "Stop"

$localDir = Split-Path $MyInvocation.MyCommand.Path

# Switch to script dir
cd $localDir

# create version file
Invoke-Expression ((Split-Path $MyInvocation.InvocationName) + "\mkversion.ps1" + " $args")

# run autotools
autoreconf -is