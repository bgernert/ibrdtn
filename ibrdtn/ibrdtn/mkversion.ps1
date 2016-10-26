$ErrorActionPreference = "Stop"

$localDir = Split-Path $MyInvocation.MyCommand.Path

# Switch to script dir
cd $localDir

# Extract the latest version
(Get-Content debian/changelog -First 1) -match "[a-z\-]* \((.*)\) .*$" | Out-Null
$version = $matches[1]

# ... and set it as default
$major = $version.Split(".")[0]
$minor = $version.Split(".")[1]
$micro = $version.Split(".")[2]

# Create a version.inc file
if(($args[0] -is [int]) -and ($args[1] -is [int])) {
    $major = $args[0]
    $minor = $args[1]

    if($args[2] -is [int]) {
        $micro = $args[2]
    }
}

"set version to $major.$minor.$micro"

# Write version to version.m4 file
"m4_define([PKG_FULL_VERSION], [$major.$minor.$micro])" | Out-File version.m4
"m4_define([PKG_LIB_VERSION], [1:0:0])" | Out-File -Append version.m4
"m4_define([PKG_MAJOR_VERSION], [$major])" | Out-File -Append version.m4
"m4_define([PKG_MINOR_VERSION], [$minor])" | Out-File -Append version.m4
"m4_define([PKG_MICRO_VERSION], [$micro])" | Out-File -Append version.m4