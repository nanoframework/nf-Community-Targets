# collection of Community targets
$communityTargets = "I2M_ELECTRON_NF", "I2M_OXIGEN_NF", "ST_NUCLEO_F411RE_EX", "ST_NUCLEO64_F411RE_NF"

# get commit message
$commitMessage = "$env:APPVEYOR_REPO_COMMIT_MESSAGE" + " " + "$env:APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED"

# nothing to build 
$env:TARGET_TO_BUILD = "NOTHING_TO_BUILD"

# is there a target name in the commit message?
$targetCandidate = [regex]::Match("$commitMessage",'[#]+\w+[#]').Value

# special case for #ALL# (build all targets)
if($targetCandidate -eq '#ALL#')
{
    # target to build is the board name
    $env:TARGET_TO_BUILD = $env:BOARD_NAME

    Write-Host "Target board is " $env:BOARD_NAME
}
elseif($targetCandidate -ne '')
{
    # remove the leading and trailinig '#'
    $targetCandidate = $targetCandidate -replace "#", ""

    # check if it's one of the supported targets
    If($communityTargets -contains $targetCandidate)
    {
        $env:TARGET_TO_BUILD = $targetCandidate

        Write-Host "Target board is " $env:TARGET_TO_BUILD        
    }
}
