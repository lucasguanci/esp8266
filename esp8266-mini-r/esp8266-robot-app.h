/* paste here content of esp8266-robot-app.html */
const char webpageCode[] = 
R"=====(
<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta name="description" content="WebSocket interface for a ESP8266-controlled robot">
  <meta name="author" content="Luca Sguanci">
  <title>WebSocket interface for a Robot</title>
  <style>
    .robot-cnt {
      margin: 1em auto;
    }
    table {
      text-align: center;
    }
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
      padding: 1em;
      font-weight: bold;
    }
  </style>
</head>

<body>
  <h3>Robot Control</h3>
  <div class="container">
    <table class="robot-cnt">
      <thead></thead>
      <tbody>
        <tr>
          <td></td>
          <td>
            <button type="button" class="btn" id="btnForward">Forward</button>
          </td>
          <td></td>
        </tr>
        <tr>
          <td>
            <button type="button" class="btn" id="btnLeft">Left</button>
          </td>
          <td>
            <button type="button" class="btn" id="btnStop">Stop</button>
          </td>
          <td>
            <button type="button" class="btn" id="btnRight">Right</button>
          </td>
        </tr>
        <tr>
          <td></td>
          <td>
            <button type="button" class="btn" id="btnBackward">Backward</button>
          </td>
          <td></td>
        </tr>
      </tbody>
    </table>
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

    // forward
    const btnForward = document.getElementById("btnForward");
    btnForward.addEventListener("mousedown", function(e) {
      console.log("moving fw.. (mouse)");
      connection.send("rForward");
    });
    btnForward.addEventListener("mouseup", function(e) {
      console.log("halting robot (mouse)");
      connection.send("rStop");
    });
    btnForward.addEventListener("touchstart", function(e) {
      e.preventDefault();
      console.log("moving fw.. (touch)");
      connection.send("rForward");
    });
    btnForward.addEventListener("touchend", function(e) {
      e.preventDefault();
      console.log("halting robot (touch)");
      connection.send("rStop");
    });
    // left
    const btnLeft = document.getElementById("btnLeft");
    btnLeft.addEventListener("mousedown", function(e) {
      console.log("turning left..");
      connection.send("rLeft");
    });
    btnLeft.addEventListener("mouseup", function(e) {
      console.log("halting robot");
      connection.send("rStop");
    });
    btnLeft.addEventListener("touchstart", function(e) {
      e.preventDefault();
      console.log("moving left.. (touch)");
      connection.send("rLeft");
    });
    btnLeft.addEventListener("touchend", function(e) {
      e.preventDefault();
      console.log("halting robot (touch)");
      connection.send("rStop");
    });
    // right
    const btnRight = document.getElementById("btnRight");
    btnRight.addEventListener("mousedown", function(e) {
      console.log("turning right..");
      connection.send("rRight");
    });
    btnRight.addEventListener("mouseup", function(e) {
      console.log("halting robot");
      connection.send("rStop");
    });
    btnRight.addEventListener("touchstart", function(e) {
      e.preventDefault();
      console.log("moving right.. (touch)");
      connection.send("rRight");
    });
    btnRight.addEventListener("touchend", function(e) {
      e.preventDefault();
      console.log("halting robot (touch)");
      connection.send("rStop");
    });
    // backward
    const btnBackward = document.getElementById("btnBackward");
    btnBackward.addEventListener("mousedown", function(e) {
      console.log("moving backward..");
      connection.send("rBackward");
    });
    btnBackward.addEventListener("mouseup", function(e) {
      console.log("halting robot");
      connection.send("rStop");
    });
    btnBackward.addEventListener("touchstart", function(e) {
      e.preventDefault();
      console.log("moving bw.. (touch)");
      connection.send("rBackward");
    });
    btnBackward.addEventListener("touchend", function(e) {
      e.preventDefault();
      console.log("halting robot (touch)");
      connection.send("rStop");
    });
    // stop
    const btnStop = document.getElementById("btnStop");
    btnStop.addEventListener("click", function(e) {
      console.log("halting robot..");
      connection.send("rStop");
    });
  </script>
</body>
</html>
)=====";