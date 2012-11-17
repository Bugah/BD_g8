<?php
	//Start session
	session_start();
	
	//Unset the variables stored in session
	unset($_SESSION['SESS_MEMBER_ID']);
	unset($_SESSION['SESS_FIRST_NAME']);
	unset($_SESSION['SESS_LAST_NAME']);
?>
<!DOCTYPE HTML>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>FindIt - Logout</title>
<!-- <link href="loginmodule.css" rel="stylesheet" type="text/css" /> -->
<link href="../style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<?php require_once 'menu.php'; ?>
<h1>Logout </h1>
<p align="center">&nbsp;</p>
<h4 align="center" class="err">Você se desconectou do seu usuário.</h4>
<!-- <p align="center">Clique aqui para <a href="login-form.php">logar</a></p> -->
</body>
</html>
