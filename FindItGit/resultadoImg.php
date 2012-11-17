<!-- Página que retorna o resultado da busca visual !-->

<!DOCTYPE HTML>
<?php
//print_r($_SESSION['img']);
require_once 'connect.php';

// Obtendo o offset para divir a busca por páginas de resposta
if (isset($_REQUEST["nPage"])) {
	$offset = $_REQUEST["nPage"];
	// Pega o número da página
} else {
	//$_SESSION["texto"] = $_REQUEST["texto"];
	// Primeira página
	$offset = 0;
}

//echo "SELECT Nome FROM TABIMG where Tags like '% ". $_SESSION["texto"] ." %' LIMIT 10 OFFSET ".$offset.";"; //debug

// Query das 10 próximas imagens
$result = "";

// Query do número de resultados
$conta = sizeof($_SESSION['img']);


?>
<html>

	<head>
		<!-- incluindo jQuery !-->
		<script src="jquery-1.8.2.min.js"></script>
		<script>
			$(".desc").hide();
			$(".score").hide();
			$(".img").hover(function() {
				$(this).find("div").toggle(500);
				$(this).find("span").toggle(500);
			});
			
			$(".linha").hover(function() {
				$(this).css("cursor", "sw-resize");
			});
			
			xtmp = $(".linha").css("padding-left");
			$(".linha").click(function() {
				var y = $(this).find("img").css("max-height");
				i = parseInt(y);
				//alert(i);
				if(i<400) {
					i = i + 200;
					x=0+"px";
				}
				else {
					i = 200;
					x=200;
				}
				//f = '"'+i+"px"+'"';
				//alert(f);
				$(this).find("img").css("padding-left", 0+"px");
				$(this).find("img").css("max-height", i+"px");
				$(this).find("img").css("max-width", i+"px");
				$(this).find("img").css("max-width:hover", "100%");
				$(this).find("img").css("max-height:hover", "100%");
				//$(this).css("padding-left", x+"px");
			});
		</script>
	</head>

	<body>

		<!-- Centralizando texto !-->
		<p class="centerTxt">
		<?php
		// Imprimindo informações
		echo "Buscando por <span class='resultado'>" . "imagem" . "</span>. <br />";
		
		$_SESSION["total"] = $conta;
		echo "Foram encontrados " . $_SESSION["total"] . " resultados.<br .>";
		mostraTempo();
		?>
		</p>
		
		<p class="centerTxt">
			<?php //navPage($_SESSION["total"]); ?>
		</p>
	
		<?php if($_SESSION["total"]>0) {
		?>
<!-- 		<div class="container center"> -->
		<div class="linha" style="float:right;margin:0px;width:70%">
		<?php } ?>
		<?php
		
		// print_r($_SESSION['img']);
		// foreach ($_SESSION['img'] as $key => $vvv)
// {
		// print($vvv);
// }

// $imagens = array_splice($_SESSION['img'],10);
$imagens = $_SESSION['img'];
$iNum = 0;
//while($_SESSION['res'])
foreach ($imagens as $img)
{
		?>

		<p>
		<?php
			// Verifica se há mais imagens a serem impressas numa nova linha
			if($iNum > 0 && $iNum%2==0) {	?>
				<!-- Separa linhas  !-->
				<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
				</div>
				
				<!-- Cria outra linha !-->
				<div class="linha" style="float:right;margin:0px;width:70%;">
			<?php 
			}
			
			$iNum++;
 ?>
			<!-- Div da Imagem !-->
			<div class="img" style="float: left;">
				<!-- Div da Descrição !-->
				<div class="desc">
					<?php echo $img; ?>
				</div>
			<!-- Colocando a imagem !-->
			<a target="_blank" href= "<?php echo "builtIn/mostraImagem.php?imgName=" . $img . ".jpg"; ?>" > <img alt="Imagem sem thumbnail" src=<?php echo "builtIn/upload/fmt/cmp/".$img.".jpg"; ?> alt="<?php echo $img; ?>"  /> </a>
			<?php 
				//echo $_SESSION['points'][$iNum-1] . "<br/>";
				$offset = (2000*pow($_SESSION['points'][$iNum-1], 5));
				$calc = 100-$offset%100;
				// echo $offset . "<br />";
				// echo $_SESSION['points'][$iNum-1] . "<br />";
				// echo $calc;
				?>
				
				<br />
				<span class="score">Pontuação: <?php echo $calc; ?> </span>
			<canvas id="canvas<?php echo $img; ?>" width="100" height="15" style="border:1px solid #c3c3c3;">
			</canvas>
			<script> //get a reference to the canvas
				var ctx = $('#canvas<?php echo $img; ?>')[0].getContext("2d");
				
				var lingrad = ctx.createLinearGradient(0,0,100,15);
			    lingrad.addColorStop(0, '#EE0000');
			    lingrad.addColorStop(0.5, '#CCCC00');
			    lingrad.addColorStop(1, '#00AA00');
							
				// ctx.fillStyle = "#00A308";
				ctx.fillStyle = lingrad;
				//ctx.beginPath();
				// ctx.arc(0, 0, 10, 0, Math.PI*2, true); 
				// ctx.rect(0,0,<?php echo $calc; ?>,15);
				ctx.fillRect(0,0,<?php echo $calc; ?>,15)
				//ctx.closePath();
				ctx.fill();
			</script>
			
			</div>

		<?php
		}
		?>
		</p>
		<br />

	<?php if($_SESSION["total"]>0) {
	?>
			<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
			</div>
			</div>
	<?php } ?>
<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
	<p class="centerTxt">
			<?php //navPage($_SESSION["total"]); ?>
		</p>


		
	</body>
</html>