<?php
$allowedExts = array("jpg", "jpeg", "gif", "png");
$extension = end(explode(".", $_FILES["file"]["name"]));
if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/png")
|| ($_FILES["file"]["type"] == "image/pjpeg"))
&& ($_FILES["file"]["size"] < 200000)
&& in_array($extension, $allowedExts))
  {
  if ($_FILES["file"]["error"] > 0)
    {
    echo "Error: " . $_FILES["file"]["error"] . "<br />";
    }
  else
    {
    echo "Upload: " . $_FILES["file"]["name"] . "<br />";
    echo "Type: " . $_FILES["file"]["type"] . "<br />";
    echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
    echo "Stored in: " . $_FILES["file"]["tmp_name"];
    
    }
  }
else
  {
  	if ((($_FILES["file"]["type"] != "image/gif")
	|| ($_FILES["file"]["type"] != "image/jpeg")
	|| ($_FILES["file"]["type"] != "image/png")
	|| ($_FILES["file"]["type"] != "image/pjpeg"))) 
	{
  		echo "Tipo de arquivo inválido. <br>".$_FILES["file"]["type"]." não é JPEG/PNG/GIF.";
	}
	else if(($_FILES["file"]["size"] > 200000)) {
		echo "Tamanho inválido. ".$_FILES["file"]["size"]."B > 2MB.";
	}
  }
?>