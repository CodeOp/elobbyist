<?php

require_once "Net/SMTP.php";
require_once dirname(__FILE__) . '/Elobbyist_IMail.inc';

class Elobbyist_NetSMTP extends Elobbyist_BaseMail implements Elobbyist_IMail {
  /*
   * Implements mail sending by PEAR Net/SMTP
  */
  public function SendMail($oInfo) {
    /*$e = "\n"; //end of line
    $bound= "==MUDDY_FUNSTER_".md5(time()); //create a unique boundary for this mail to separate each different type in the message. 

    @$smtp = new Net_SMTP("your.mailserver.ext", 25); // set to youe mail providers A record and port number (IP Addresses will also work for server)
    @$smtp->connect(60); //create connection and set timeout duration
    @$smtp->helo('your_mail_domain.ext'); //start comunication with server --change to your mail providers domain   
    @$smtp->auth($user, $pass);  //authenticate account
    @$smtp->mailFrom("$sender");  //email address of authenticated account, can set default in function declaration
    @$smtp->rcptTo("$destination");   //recipient of mail, can set default in function declaration

    $header = "";  //set header as empty 
    $header .= "From: $to <$sender>".$e; // Set Friendly Name and address of sender
    $header .= "To: $from <$destination>".$e; // Set Friendly name and address of recipient
    $header .= "Subject: $subject".$e;  //Set mail Subject
    $header .= "Reply-To: $sender".$e;  //Set Reply-to address
    $header .= 'MIME-Version:1.0'.$e;   //use MIME transport
    $header .= "Content-type:multipart/mixed;"; // Define multipart mail contnent
    $header .= "boundary=\"".$bound."\"".$e.$e; //set unique boundary for each different type of content

    $message = $header; //include headers into message information
    $message .= "--".$bound.$e; //open boundary
    $message .= "Content-type:text/html;";  //set contnent as html for mail body
    $message .= "charset=\"iso-8859-1\";".$e; //set charactor set to be used in mail body - can be changed to suit
    $message .= "Content-disposition:inline;"; //use inline to inferr displaying of contnet in the body without need for end user input
    $message .= "Content-transfer-encoding:quoted-printable".$e.$e.$e; //set transfer encoding for html text content
    $message .= $body.$e.$e; //add the contnent of $body which is passed into the function 
    if($attachment != null && $fName != null){ //check if there is an attchment being passed into the function and that it has a name
    $message .= "--".$bound.$e; //add boundary to change to next content type
    $message .= "Content-type:application/octet-stream;"; //set content type to suitable type for attachment (octet-stream is for generic binary data other are available)
    $message .= "name=\"$fName.xml\"".$e; //set the file name
    $message .= "Content-disposition:attachment;"; //use attachment to infer data that is being passed as a file
    $message .= "filename=\"$fName.xml\";".$e; //set the filename as it will be recieved
    $message .= "Content-transfer-encoding:base64".$e.$e; // encode the file for transfer
    $message .= $attachment.$e.$e; // add attachment contents
    }
    $message .= "--$bound--".$e; //closing boundary shows it's the last part of the MIME and the mail is now complete

    @$smtp->data($message); //send message to the server
    $msg = $smtp->getResponse(); // get server response array format -- $msg = Array([0]=>'server numeric code' [1]=>'Text message from server for code') -- hMailServer success response code is 250.  This can be called after any of the $smtp-> calls for error capture 
    @$smtp->disconnect(); // close server connection
    return $msg; //pass out server response array
    */
  }
}