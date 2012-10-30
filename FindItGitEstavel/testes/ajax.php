<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
	"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<style type="text/css">
		@import "../style.css"
	</style>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="en" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
	<title>title</title>
</head>
<body>

<div id="upInfo" style="background-color:#FFFFAA;height:250px;width:400px;margin-left:500px;float:left;">
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

	// Se ocorrer erro no upload  	
  if ($_FILES["file"]["error"] > 0)
    {
    echo "Error: " . $_FILES["file"]["error"] . "<br />";
    }
	// Erro de tipo de entrada
  else
    {
    ?><i><?php
    echo "Upload: " . $_FILES["file"]["name"] . "<br />";
    echo "Tipo: " . $_FILES["file"]["type"] . "<br />";
    echo "Tamanho: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
    echo "Localizado em: " . $_FILES["file"]["tmp_name"]. " <br /><br />";
    ?></i><?php
    }
    if (file_exists("upload/" . $_FILES["file"]["name"]))
      {
      echo $_FILES["file"]["name"] . " já existe. ";
      }
    else
      {
      move_uploaded_file($_FILES["file"]["tmp_name"],
      "upload/" . $_FILES["file"]["name"]);
      echo "Local do arquivo: " . "builtIn/upload/" . $_FILES["file"]["name"];
      }
  }
	else
  {
  	echo "<h2>Erro</h2>";
	echo $_FILES["file"]["name"];
  	if ((($_FILES["file"]["type"] != "image/gif")
	|| ($_FILES["file"]["type"] != "image/jpeg")
	|| ($_FILES["file"]["type"] != "image/png")
	|| ($_FILES["file"]["type"] != "image/pjpeg"))) 
	{
  		echo "<br />Tipo de arquivo inválido. <br>".$_FILES["file"]["type"]." não é do tipo JPEG/PNG/GIF válido.";
	}
	else if(($_FILES["file"]["size"] > 200000)) {
		echo "Tamanho inválido. ". ($_FILES["file"]["size"] / 1024)."Kb > 2MB.";
	}
	else {
		echo "Erro desconhecido. ";
	}
  }
?>
<p><input type="button" value="Sair" onclick="window.location='../index.php'" /></p>
</div>

<?php if ($_FILES["file"]["error"] <= 0) { ?>
<div style="padding-top: 300px;">
<h2>Visualização da Imagem:</h2>
<img src="<?php echo "upload/".$_FILES["file"]["name"]; ?>" />
</div>
<?php } ?>

</body>
</html>