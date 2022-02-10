/* paste here content of led-control-app.html */
const char webpageCode[] = 
R"=====(
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="description" content="WebSocket interface for a RGB Arduino-controlled LED">
  <meta name="author" content="Luca Sguanci">
  <title>WebSocket interface for a RGB Arduino-controlled LED</title>
  <!-- Bootstrap core CSS -->
  <!-- <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous"> -->
  <style>
    h3 {
      font-size: 120%;
      text-align: center;
      margin: 2em auto;
    }
    .row {
      margin-bottom: 1em;
    }
    .col-sm {
      text-align: center;
    }
    button {
      margin-top: 2em;
    }
  </style>
</head>

<body>
  <h3>Control a RGB LED color</h3>
  <div class="container">
    <!-- red -->
    <div class="row">
      <div class="col-sm">
        <label for="redField">Red</label>
      </div>
      <div class="col-sm">
        <input type="range" id="red" name="redField" min=0 max=255 step=1 />
      </div>
    </div>
    <!-- green -->
    <div class="row">
      <div class="col-sm">
        <label for="greenField">Green</label>
      </div>
      <div class="col-sm">
        <input type="range" id="green" name="greenField" min=0 max=255 step=1 />
      </div>
    </div>
    <!-- blue -->
    <div class="row">
      <div class="col-sm">
        <label for="blueField">Blue</label>
      </div>
      <div class="col-sm">
        <input type="range" id="blue" name="blueField" min=0 max=255 step=1 />
      </div>
    </div>
    <!-- button -->
    <div class="row">
      <div class="col-sm">
        <button type="button" class="btn btn-primary" id="changeColorBtn">Change color</button>
      </div>
    </div>
  </div>
  <!-- JS -->
  <!-- if needed include jQuery, Popper and Bootstrap -->
  <!-- Custom JS code -->
  <script>
    // comment to work disconnected from the ESP8266
    var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
    // uncomment to work disconnected from the ESP8266
    // var connection = new WebSocket('ws://localhost:81/', ['arduino']);
    connection.onopen = function () {
      connection.send('Connect ' + new Date());
    };
    connection.onerror = function (error) {
      console.log('WebSocket Error ', error);
    };
    connection.onmessage = function (e) {
      console.log('Server: ', e.data);
    };
    connection.onclose = function () {
      console.log('WebSocket connection closed');
    };

    const redSlider = document.getElementById("red");
    redSlider.addEventListener("change", changeColorHandler);
    const greenSlider = document.getElementById("green");
    greenSlider.addEventListener("change", changeColorHandler);
    const blueSlider = document.getElementById("blue");

    const btn = document.getElementById('changeColorBtn');

    var color = Array();
    var colorString = new String();

    blueSlider.addEventListener("change", changeColorHandler);
    function changeColorHandler() {
      console.log("inside");
      var r = document.getElementById('red').value;
      var g = document.getElementById('green').value;
      var b = document.getElementById('blue').value;
      color = [];
      color.push(parseInt(r).toString(16).padStart(2,'0'));
      color.push(parseInt(g).toString(16).padStart(2,'0'));
      color.push(parseInt(b).toString(16).padStart(2,'0'));
      colorString = '#';
      for (var i=0; i<color.length; i++) {
         colorString += color[i];
      }
      console.log("Color: "+colorString);
      btn.style.backgroundColor = colorString;
    }

    btn.addEventListener('click', function(e) {
      console.log("Color: "+colorString);
      connection.send(colorString);
    });
  </script>
</body>
</html>
)=====";