#cs ----------------------------------------------------------------------------

    WebDMA
    Copyright (C) 2009-2010 Dustin Spicuzza <dustin@virtualroadside.com>
    
    $Id$

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License v3 as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    
    This is an automated installer script to deploy WebDMA onto a FRC Robot
    system. Compile this with AutoIt
 

#ce ----------------------------------------------------------------------------


#Include <FTPEx.au3>
#Include <String.au3>

; various paths / settings
$tempFile = @TempDir & "\ni-rt.ini"

$object_name = "WebDMA.out"
$local_object_name =  @ScriptDir & "\" & $object_name
$remote_object_name = "/ni-rt/system/" & $object_name

$local_www_dir = @Scriptdir & "\www"
$remote_www_dir= "/www"


; use the development object if we're developing/debugging
If FileExists( @ScriptDir & "\..\src\PPC603gnu\WebDMA\NonDebug\" & $object_name ) Then
	$local_object_name = @ScriptDir & "\..\src\PPC603gnu\WebDMA\NonDebug\" & $object_name
EndIf

; same thing for www directory
If FileExists( @ScriptDir & "\..\www" ) Then
	$local_www_dir = @ScriptDir & "\..\www"
EndIf


; before we make any changes, make sure the necessary files are where
; we expect them to be

If Not FileExists( $local_object_name ) Then
	MsgBox( 48, "Error", "Cannot locate local object file at " & $local_object_name )
	Exit 1
EndIf

If Not FileExists( $local_www_dir ) Then
	MsgBox( 48, "Error", "Cannot locate local www directory at " & $local_www_dir )
	Exit 1
EndIf


; draconian warning just in case

If MsgBox( 36, "WARNING WARNING WARNING", "WARNING: This script will WRITE DIRECTLY TO YOUR ROBOT and modify files on it via FTP if you choose to continue." & @CRLF & @CRLF & "While I have tested this and this works just fine for our team on our cRio with no ill effects, I cannot be held responsible for your robot. This installer is not sanctioned or associated with National Instruments, Wind River, or FIRST Robotics. In particular, this may void your warranty, render your cRio useless, and COST YOUR TEAM A LOT OF MONEY." & @CRLF & @CRLF & "If you are a student: DO NOT INSTALL THIS ON YOUR ROBOT WITHOUT ASKING THE ADULT LEADER OF YOUR TEAM." & @CRLF & @CRLF & "Click Yes to install WebDMA on your robot. Are you willing to accept these risks?") = 7 Then
	Exit 5
EndIf


; Load the team number from the registry if its already there
$registryKey = "HKCU\Software\WebDMA"
$registryValue = "TeamNumber"

$teamNumber = RegRead($registryKey, $registryValue)

; Get the team number from the user
Do
	$teamNumber = InputBox( "Enter your team number", "Team Number", $teamNumber )
	$teamNumber = Int($teamNumber)
	
	If $teamNumber = 0 and @Error = 1 Then
		Exit 1
	EndIf 
	
Until $teamNumber <> 0

; Save that somewhere so they dont have to retype it each time
RegWrite($registryKey, $registryValue, "REG_SZ", $teamNumber)


; calculate the server IP from the team number
$server = "10." & Int( $teamNumber / 100 ) & "." & Mod( $teamNumber , 100) & ".2"

ProgressOn( "WebDMA Robot Installation", "Installing to your robot at " & $server )

ProgressSet( 0, "Opening FTP handle" )

; If we don't get the handle, then oops
$inet_handle = _FTP_Open( $object_name & " FTP Deployment" )
If $inet_handle = 0 Then
	ProgressOff()
	MsgBox( 48, "Error opening FTP handle" )
	Exit 1
EndIf

ProgressSet( 10, "Connecting to FTP Server @ " & $server )

$ftp_handle = _FTP_Connect( $inet_handle, $server, "FRC", "FRC", 1 )
If  $ftp_handle = 0 Then
	ProgressOff()
	MsgBox( 48, "Error", "Error connecting to Robot FTP Server at " & $server )
	Exit 1
EndIf


; modify the NI-RT file
ProgressSet( 20, "Retrieving /ni-rt.ini" )

If _FTP_FileGet( $ftp_handle, "/ni-rt.ini", $tempFile ) = 0 Then
	ProgressOff()
	MsgBox( 48, "Error", "Error " & @Error & " getting /ni-rt.ini from the robot")
	Exit 1
EndIf

ProgressSet( 30, "Modifying ni-rt.ini file" )

$dlls = IniRead( $tempFile, "LVRT", "StartupDlls", "")

If StringInStr( $dlls, $object_name & ";" ) = 0 Then

	$dlls = StringStripWS($dlls, 2)
	If StringRight( $dlls, 1 ) <> ";" Then
		$dlls = $dlls & ";"
	EndIf

	; make sure this loads before FRC_UserProgram.out
	$user_pos = StringInStr( $dlls, "FRC_UserProgram.out" )
	
	If $user_pos <> 0 Then
		$dlls = _StringInsert( $dlls, $object_name & ";", $user_pos - 1 )
	Else
		$dlls = $dlls & $object_name & ";"
	EndIf

	IniWrite( $tempFile, "LVRT", "StartupDlls", $dlls)

	ProgressSet(45, "Uploading new ni-rt.ini file" )
	
	_FTP_FilePut( $ftp_handle, $tempFile, "/ni-rt.ini" )
	
EndIf

FileDelete( $tempFile )

; Write the object file to the robot
ProgressSet( 60, "Uploading " & $object_name  & " to " & $remote_object_name)


If _FTP_FilePut( $ftp_handle, $local_object_name, $remote_object_name) = 0 Then
	ProgressOff()
	MsgBox( 48, "Error", "Error " & @Error & " writing " & $objectName & " to server" )
	Exit 2
EndIf
	
	
; write the HTML files to the webserver

ProgressSet( 80, "Uploading HTML files to " & $remote_www_dir )

If FileExists( $local_www_dir ) = 0 Then
	ProgressOff()
	MsgBox( 48, "Error", "Local www directory ( " & $local_www_dir & " ) was not found " )
	Exit 1
EndIf

; for each file in www, write it out
_FTP_DirCreate($ftp_handle, $remote_www_dir)

If _FTP_DirPutContents($ftp_handle, $local_www_dir, $remote_www_dir, 1) = 0 Then
	ProgressOff()
	MsgBox( 48, "Error", "Error " & @Error & " writing to server " & $server )
	_FTP_Close( $ftp_handle )
	Exit 1
EndIf
	
ProgressSet( 100, "Done" )
	
_FTP_Close( $ftp_handle )
	
ProgressOff()

MsgBox( 0, "Success!", "All files have been successfully transferred to your robot")
MsgBox( 0, "Success!", "You must reboot your cRio!")


