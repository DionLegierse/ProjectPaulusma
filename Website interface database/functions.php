<?php
	function getTemperature($postNameTemperature){
		$temperature;
		if(isset($_POST[$postNameTemperature])){
			$temperature = $_POST[$postNameTemperature];
			
			if($temperature <= 800 && $temperature >= -100){
				echo "<p> De temperatuur is: $temperature graden celsius. </p>";
			}else{
				echo "<p> Ongeldige temperatuur is aangeleverd. </p>";
			}
			
			return $temperature;
		}
	}
	
	function getHumidity($postNameHumidity){
		$humidity;
		if(isset($_POST[$postNameHumidity])){
			$humidity = $_POST[$postNameHumidity];
			
			if($humidity <= 100 && $humidity >= 0){
				echo "<p> De luchtvochtigheid is: $humidity procent vochtig. </p>";
			}else{
				echo "<p> Ongeldige luchtvochtigheid is aangeleverd. </p>";
			}
			
			return $humidity;
		}	
	}
	
	function getPressure($postNamePressure){
		$pressure;
		if(isset($_POST[$postNamePressure])){
			$pressure = $_POST[$postNamePressure];
			
			if($pressure <= 1050 && $pressure >= 1000){
				echo "<p> De luchtdruk is: $pressure millibar. </p>";
			}else{
				echo "<p> Ongeldige luchtdruk is aangeleverd. </p>";
			}
			
			return $pressure;
		}	
	}
	
?>