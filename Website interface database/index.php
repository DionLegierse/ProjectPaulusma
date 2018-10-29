<!DOCTYPE HTML>
<head>
	<meta charset="utf-8">
	<title> de coole dion pagina </title>
	<link href="style.css" type="text/css" rel="stylesheet" />
</head>

<body">
	<div>
		<?php
			include 'functions.php';
			
			$temperature = getTemperature("temperature");
			$humidity = getHumidity("humidity");
			$pressure = getPressure("pressure");
			
			$servername = "databases.aii.avans.nl";
			$username = "dallegie";
			$password = "Ab12345";
			
			$conn = new mysqli($servername, $username, $password);
			
			echo $conn->error;
			
			mysqli_select_db($conn,"dallegie_db");
			
			$sql = "INSERT INTO tblvalue (intPressure, intTemperature, intHumidity)
					VALUES ('$pressure','$temperature','$humidity')";
			
			$conn->query($sql);
			
			$sql ="INSERT INTO tbldateandtime (dateDate, timeTime)
					VALUES (current_date(),current_time())";
			$conn->query($sql);
			
			$sql ="INSERT INTO tbldateandtimevalue (TimeID, ValueID)
					VALUES (last_insert_id(),last_insert_id())";
			if ($conn->query($sql) === TRUE) {
				echo "New record created successfully";
			} else {
				echo "Error: " . $sql . "<br>" . $conn->error;
			}

			
		?>
	</div>
</body>