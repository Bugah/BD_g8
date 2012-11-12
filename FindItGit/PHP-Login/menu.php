<script src="jquery-1.8.2.min.js"></script>
<ul id="listaPrincipal" class="center">
	<a href="../index.php"><img style="float:left;" src="imagens/secLogo.png" height="70px" /></a>
	<li>
		<a href="../buscaImagem.php?buscaTipo=Texto"><img class="texto" title="texto" src="imagens/transp50.png"/> Texto</a>
	</li>
	<li>
		<a href="../buscaImagem.php?buscaTipo=Imagem"><img class="imagem" title="imagem" src="imagens/transp50.png"/> Imagem</a>
	</li>
	<li>
		<a href="../inserir.php">Inserir Imagem</a>
	</li>
	
    <?php if(isset($_SESSION['SESS_MEMBER_ID'])) { ?>
    <div class="menu" style="float:right">
         <?php echo $_SESSION['SESS_MEMBER_ID']; ?>
         <a href="logout.php">logout</a>
    </div>
    <?php } else { ?>
    	<li style="border-style:inset;">
	        <a href="login-form.php">Login</a>
	    </li>
	<?php } ?>
	<!-- <li style="float:right;">
        <a onclick="$('#login').load('PHP-Login/login-form.php');" href="">Login</a>
    </li>
    <li style="float:right;">
        
    </li> -->
</ul>
