#ifndef PRIVATE_HTML_H
#define PRIVATE_HTML_H

#include <Arduino.h>

String INDEX_HTML = R"(<!DOCTYPE html>
<!DOCTYPE html>
<html>
<head>

   <title>Motor Control</title>

   <meta name="viewport" content="width=device-width, initial-scale=1">

   <style>

   html,body{
      width:100%;
      height:100%;
      margin:0}
   *{box-sizing:border-box}
   .colorAll{
      background-color:#90ee90}
   .colorBtn{
      background-color:#add8e6}
   .angleButtdon,a{
      font-size:30px;
      border:1px solid #ccc;
      display:table-caption;
      padding:7px 10px;
      text-decoration:none;
      cursor:pointer;
      padding:5px 6px 7px 10px}a{
      display:block}
   .btn{
      margin:5px;
      border:none;
      display:inline-block;
      vertical-align:middle;
      text-align:center;
      white-space:nowrap}
   </style>
</head>
<body>
<h1>Motor Control</h1>
)";

#endif /* PRIVATE_HTML_H */
