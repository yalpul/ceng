<!DOCTYPE html>
<html>
  <head>
    <title>CENG495 Homework 1</title>
  </head>
<body>
<form>
<h3>CENG495 CLOUD COMPUTING HOMEWORK 1</h3>

  Background Color:
  <select name="bgcolor" id="bgcolor">
    <option selected="selected" value="fff">White</option>
    <option value="000">Black</option>
    <option value="f00">Red</option>
    <option value="0f0">Green</option>
    <option value="00f">Blue</option>
  </select>
  <br>

  Foreground Color:
  <select name="fgcolor" id="fgcolor">
    <option value="fff">White</option>
    <option selected="selected" value="000">Black</option>
    <option value="f00">Red</option>
    <option value="0f0">Green</option>
    <option value="00f">Blue</option>
  </select>
  <br>

  Text: 
  <input type="text" name="text" id="text">
  <br>

  <input type="submit" name="btn" id="btn" value="Generate">
</form>

<br>
<?php
  $style = 'color:White;background-color:'.
      'White;border-color:White;border-width:0px;border-style:None;'.
      'height:150px;width:150px;';
  $bg = $_GET['bgcolor'];
  $fg = $_GET['fgcolor'];
  $data = $_GET['text'];
  if ($_GET['btn']) {
  echo '<img id="imgbox" src='.
    "\"https://api.qrserver.com/v1/create-qr-code/?size=150x150&data=$data&color=$fg&bgcolor=$bg\" ".
    "style=\"$style\">";
  }
  else {
    echo '<img id="imgbox" style='."\"$style\">";
  }
?>

<h4>File Upload Mode</h4>
<form action="http://api.qrserver.com/v1/read-qr-code/" method="POST" enctype="multipart/form-data">
  <input type="hidden" name="MAX_FILE_SIZE" value="1048576">
  <input name="file" type="file"><br>
  <input type="submit" value="Upload">
</form>
</body>
</html>
