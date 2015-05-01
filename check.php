<?php
	//MySQL DB Connection
    $servername="192.168.0.200";
	$username="root";
	$password="password";
	
	//Create Connection
	$con= mysql_connect($servername,$username,$password);
	//Check Connection
	if (! $con ) {
		die('Connection failed: ' . mysql_error());
	}
	// Prepare the SQL statement
    $Sql = "SELECT COUNT(*) FROM mydb.user WHERE card_id = '".$_GET["key"]."' "; 
	$retval = mysql_query($Sql,$con);
	
	//Check for Return Data
	if(! $retval )
	{
		die('Could not get data' . mysql_error());
	}
	while($row=mysql_fetch_array($retval, MYSQL_NUM)){
	//Check if user exists
		if ($row[0] == 1){
			echo '|1';
		}
		else{
			echo '|0';
		}
		
	}
	mysql_close($con);

?>
