<?php
	//Start session
	session_start();
	
	//Include database connection details
	require_once('config.php');
	
	//Array to store validation errors
	$errmsg_arr = array();
	
	//Validation error flag
	$errflag = false;
	
	//Connect to mysql server
	$link = mysql_connect(DB_HOST, DB_USER, DB_PASSWORD);
	if(!$link) {
		die('Failed to connect to server: ' . mysql_error());
	}
	
	//Select database
	$db = mysql_select_db(DB_DATABASE);
	if(!$db) {
		die("Unable to select database");
	}
	
	//Function to sanitize values received from the form. Prevents SQL injection
	function clean($str) {
		$str = @trim($str);
		if(get_magic_quotes_gpc()) {
			$str = stripslashes($str);
		}
		return mysql_real_escape_string($str);
	}
	
	//Sanitize the POST values
	$fname = clean($_POST['nome']);
	$lname = clean($_POST['sobrenome']);
	$login = clean($_POST['login']);
	$password = clean($_POST['senha']);
	$cpassword = clean($_POST['csenha']);
	
	//Input Validations
	if($fname == '') {
		$errmsg_arr[] = 'Campo Nome vazio';
		$errflag = true;
	}
	if($lname == '') {
		$errmsg_arr[] = 'Campo Sobrenome vazio';
		$errflag = true;
	}
	if($login == '') {
		$errmsg_arr[] = 'Login Vazio';
		$errflag = true;
	}
	if($password == '') {
		$errmsg_arr[] = 'Falta senha';
		$errflag = true;
	}
	if($cpassword == '') {
		$errmsg_arr[] = 'Falta confirmacao de senha';
		$errflag = true;
	}
	if( strcmp($password, $cpassword) != 0 ) {
		$errmsg_arr[] = 'As senhas nao batem';
		$errflag = true;
	}
	
	//Check for duplicate login ID
	if($login != '') {
		$qry = "SELECT * FROM Usuarios WHERE login='$login'";
		$result = mysql_query($qry);
		if($result) {
			if(mysql_num_rows($result) > 0) {
				$errmsg_arr[] = 'Login ja existente';
				$errflag = true;
			}
			@mysql_free_result($result);
		}
		else {
			die("Query failed");
		}
	}
	
	//Se existiu algum erros, voltar para a pagina
	if($errflag) {
		$_SESSION['ERRMSG_ARR'] = $errmsg_arr;
		session_write_close();
		header("location: register-form.php");
		exit();
	}

	//Create INSERT query
	$qry = "INSERT INTO Usuarios(Nome, Sobrenome, Login, Senha) VALUES('$fname','$lname','$login','".md5($_POST['senha'])."')";
	$result = @mysql_query($qry);
	
	//Check whether the query was successful or not
	if($result) {
		header("location: register-success.php");
		exit();
	}else {
		die("Query failed");
	}
?>