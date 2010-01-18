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

; Script Start - Add your code below here

#Include <FTPEx.au3>

; Load the team number from the registry if its already there
$registryKey = "HKCU\Software\WebDMA"
$registryValue = "TeamNumber"


$teamNumber = RegRead($registryKey, $registryValue)

; Get the team number from the user
Do
	$teamNumber = InputBox( "Enter your team number", "Team Number", $teamNumber )
	
	If $teamNumber = 0 and @Error = 1 Then
		Exit 1
	EndIf 
	
Until $teamNumber <> 0

; Save that somewhere so they dont have to retype it each time
RegWrite($registryKey, $registryValue, "REG_SZ", $teamNumber)


; calculate the server IP from the team number
$i2 = Mod( $teamNumber , 100)
$i1 = Int( $teamNumber / 100 )

$server = "10." & $i1 & "." & $i2 & ".2"

; If we don't get the handle, then oops
$inet_handle = _FTP_Open( "WebDMA FTP Deployment" )
If $inet_handle = 0 Then
	MsgBox( 48, "Error opening FTP handle" )
	Exit 1
EndIf

$ftp_handle = _FTP_Connect( $inet_handle, $server, "FRC", "FRC", 1 )
If  $ftp_handle = 0 Then
	MsgBox( 48, "Error", "Error connecting to Robot FTP Server at " & $server )
	Exit 1
EndIf

; modify the NI-RT file
; _FTP_FileGet( $ftp_handle, "/ni-rt.ini" )
; IniFileWrite( )
;
; Write the object file to the robot
If _FTP_FilePut( $ftp_handle, @ScriptDir & "\WebDMA.out") = 0 Then
	MsgBox( 48, "Error", "Error " & @Error & " writing .out file to server" )
	Exit 2
EndIf
	
	
; write the HTML files to the webserver

; for each file in www, write it out
_FTP_DirCreate($ftp_handle, "/www")
If _FTP_DirPutContents($ftp_handle, @ScriptDir & "\www", "/www", 1) = 0 Then
	MsgBox( 48, "Error", "Error " & @Error & " writing to server " & $server )
	_FTP_Close( $ftp_handle )
	Exit 1
EndIf
	
_FTP_Close( $ftp_handle )
	
	; write 


MsgBox( 0, "Success!", "All WebDMA files have been successfully transferred to your robot")


