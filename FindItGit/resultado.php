<!DOCTYPE HTML>

<html>

	<head>
		<title>Busca via Imagem</title>
		<style>
			@import "style.css";
		</style>
		<script src="jquery-1.8.2.min.js"></script>
		<script>
			$(document).ready(function() {
				$(".desc").hide();
				$(".img").hover(function() {
					$(this).find("div").toggle(500);
				});
				
				$("li").click(function() {
					$(this).css("border-style","inset");
				});
				
			});
			
			function confereImg(w) {
				if(w.value) {
					document.getElementById("myButton").disabled=false;
				}
			}
			
			function loadXMLDoc() {
					var xmlhttp;
				
					if (window.XMLHttpRequest) {// code for IE7+, Firefox, Chrome, Opera, Safari
						xmlhttp = new XMLHttpRequest();
					} else {// code for IE6, IE5
						xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
					}
						xmlhttp.onreadystatechange = function() {
							if (xmlhttp.readyState==2 && xmlhttp.status==200)
							    {
							    document.getElementById("myDiv").innerHTML="Foi";
							    } 
							    
							 if (xmlhttp.readyState==3 && xmlhttp.status==200)
							    {
							    document.getElementById("myDiv").innerHTML="Aguarde";
							    } 
							
							if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
								document.getElementById("myDiv2").innerHTML = xmlhttp.responseText;
								document.getElementById("myImg").src = xmlhttp.responseText;
								//document.getElementById("myImg").src = "imagens/bigLogo.jpg";;
							}
						}
						xmlhttp.open("GET", "testes/ajax.php?file="+document.getElementById("file").value, true);
						xmlhttp.send();
				
				}
				
		</script>

	</head>

	<body>
		
		<?php
			require_once 'menu.html';
			
			if($_REQUEST['buscaTipo']=="Imagem")
				include_once "selecionaImagem.php";
			else {
				include_once 'selecionaTexto.php';
			}
			
 ?>
		
		<div class="container center">
			<div class="linha">  
		<?php
		$iNum = 0;
		$file = fopen("builtIn/upload/lista.txt", "r") or exit("Unable to open file!");
		//Output a line of the file until the end is reached
		while($img = fgets($file))
		
		{
			$iNum++;
			if($iNum==0) {
				?> <?php
			}
			?>
		<div class="img">
			<div class="desc">
				<?php echo $img; ?>
			</div>
			<a target="_blank" href= "<?php echo "builtIn/upload/" . $img; ?>" > <img src="<?php echo "builtIn/upload/" . $img; ?>" alt="<?php echo $img?>"  /> </a>
			
		</div>

		<?php
		if($iNum>0 && $iNum%3==0) {?>
					<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
					</div>
					<div class="linha">
				<?php } 
		}
		fclose($file);
		?>
		<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
<br />

</div>
	<div class="resizeble">
		<p>Oioioioi</p>
		<button id="clepto">Tchau</button>
	</div>
	
	</div>
	
	</body>

</html>