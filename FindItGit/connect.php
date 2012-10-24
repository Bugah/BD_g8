<!-- Biblioteca responsável pela conexão ao BD. Também disponibiliza algumas funções úteis. !-->
<?php
// Inicia a sessão PHP
if (!isset($_SESSION)) {
  session_start();
}

// Conecta ao banco de dados
$con = mysql_connect("localhost","findIt","bd");
if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

// some code
mysql_select_db("test", $con);

function guarda($sessao, $varv) {
	if(isset($varv)) {
		$sessao = $varv;
	} 
}

// Imprime a lista de páginas da pesquisa
function navPage($num) {
	$total = $num;
	if($total > 10) {
		$j = 0;
		while($total > 0) {
		?>
			<a href="?nPage=<?php echo 10 * $j; ?>"><?php echo $j + 1; ?></a>
		<?php
			$total -= 10;
			$j++;
		}
	}
}

// Começa a marcar o tempo de uso
function acionaTempo() {
	$_SESSION['mtime'] = microtime(); 
   	$_SESSION['mtime'] = explode(" ",$_SESSION['mtime']); 
 	$_SESSION['mtime'] = $_SESSION['mtime'][1] + $_SESSION['mtime'][0]; 
	$_SESSION['starttime'] = $_SESSION['mtime']; 
}

// Mostra o tempo gasto em relação ao acionaTempo
function mostraTempo() {
	$_SESSION['mtime'] = microtime(); 
	   $_SESSION['mtime'] = explode(" ",$_SESSION['mtime']); 
	   $_SESSION['mtime'] = $_SESSION['mtime'][1] + $_SESSION['mtime'][0]; 
	   $endtime = $_SESSION['mtime']; 
	   $totaltime = ($endtime - $_SESSION['starttime']); 
	   $fmt = number_format($totaltime,4);
	   echo "Tempo de busca: ".$fmt." segundos.";
}

function mostraTempoAlt($texto) {
	$_SESSION['mtime'] = microtime(); 
	   $_SESSION['mtime'] = explode(" ",$_SESSION['mtime']); 
	   $_SESSION['mtime'] = $_SESSION['mtime'][1] + $_SESSION['mtime'][0]; 
	   $endtime = $_SESSION['mtime']; 
	   $totaltime = ($endtime - $_SESSION['starttime']); 
	   $fmt = number_format($totaltime,4);
	   echo "Tempo de ".$texto.": ".$fmt." segundos.";
}
	?>