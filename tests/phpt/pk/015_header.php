@ok
<?php

header('X-TEST-1: value1');
header('X-TEST-1: value2');
header('X-TEST-2: value1', false);
header('X-TEST-2: value2', false);
header('X-TEST-3: value1', false);
header('X-TEST-3: value2', false);
header('X-TEST-3: value3', true);
header('Date: haha, date in tests');
setcookie('test-cookie', 'blabla');
$x = headers_list();

#ifndef KittenPHP
// not working in console php
$x = [
  'Server: nginx/0.3.33',
  'Date: haha, date in tests',
  'Content-Type: text/html; charset=windows-1251',
  'X-TEST-1: value2', 
  'X-TEST-2: value1', 
  'X-TEST-2: value2', 
  'X-TEST-3: value3', 
  'Set-Cookie: test-cookie=blabla'
];
#endif

var_dump($x);
