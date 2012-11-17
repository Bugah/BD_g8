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
		</script>

	</head>

	<body>
		
		<?php
			require_once 'menu.php';
			
			if($_REQUEST['buscaTipo']=="Imagem")
				include "selecionaImagem.php";
			else {
				include_once 'selecionaTexto.php';
			}
			
			if(isset($_REQUEST['busca']) && $_REQUEST['busca']) {
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
	
		<?php } ?>
	</body>

</html>
