#include "webDesign.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8"/>
		<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
		<meta name="apple-mobile-web-app-capable" content="yes" />
		<link rel="stylesheet" href="style.css">
		<script async src="code.js"></script>
		<title>esp32-wifi-manager</title>
	</head>
	<body>
		<div id="app">
			<div id="app-wrap">
				<div id="wifi">
					<header>
						<h1>Wi-Fi</h1>
					</header>
					<div id="wifi-status">
						<h2>Connected to:</h2>
						<section id="connected-to">
							<div class="ape"><div class="w0"><div class="pw"><span></span></div></div></div>
						</section>
					</div>
					<h2>Manual connect</h2>
					<section id="manual_add">
					<div class="ape">ADD (HIDDEN) SSID<div>
					</section>
					<h2>or choose a network...</h2>
					<section id="wifi-list">
					</section>
					<div id="pwrdby"><em>Powered by </em><a id="acredits" href="#"><strong>esp32-wifi-manager</strong></a>.</div>
				</div>
				<div id="connect_manual">
					<header>
						<h1>Enter Details</h1>
					</header>
					<h2>Manual Connection</span></h2>
					<section>
						<input id="manual_ssid" type="text" placeholder="SSID" value="">
						<input id="manual_pwd" type="password" placeholder="Password" value="">
					</section>
					<div class="buttons">
							<input id="manual_join" type="button" value="Join" data-connect="manual" />
							<input id="manual_cancel" type="button" value="Cancel"/>
					</div>
				</div>
				<div id="connect">
					<header>
						<h1>Enter Password</h1>
					</header>
					<h2>Password for <span id="ssid-pwd"></span></h2>
					<section>
						<input id="pwd" type="password" placeholder="Password" value="">
					</section>
					<div class="buttons">
							<input id="join" type="button" value="Join" />
							<input id="cancel" type="button" value="Cancel"/>
					</div>
				</div>
				<div id="connect-wait">
					<header>
						<h1>Please wait...</h1>
					</header>
					<h2>Connecting to <span id="ssid-wait"></span></h2>
					<section>
						<div id="loading">
							<div class="spinner"><div class="double-bounce1"></div><div class="double-bounce2"></div></div>
							<p class="tctr">You may lose wifi access while the esp32 recalibrates its radio. Please wait until your device automatically reconnects. This can take up to 30s.</p>
						</div>
						<div id="connect-success">
							<h3 class="gr">Success!</h3>
						</div>
						<div id="connect-fail">
							<h3 class="rd">Connection failed</h3>
							<p class="tctr">Please double-check wifi password if any and make sure the access point has good signal.</p>
						</div>
					</section>
					<div class="buttons">
						<input id="ok-connect" type="button" value="OK" class="ctr" />
					</div>
				</div>
				<div id="connect-details">
					<div id="connect-details-wrap">
						<header>
							<h1></h1>
						</header>
						<h2></h2>
						<section>
							<div class="buttons">
								<input id="disconnect" type="button" value="Disconnect" class="ctr"/>
							</div>
						</section>
						<h2>IP Address</h2>
						<section>
							<div class="ape brdb">IP Address:<div id="ip" class="fr"></div></div>
							<div class="ape brdb">Subnet Mask:<div id="netmask" class="fr"></div></div>
							<div class="ape">Default Gateway:<div id="gw" class="fr"></div></div>
						</section>
						<div class="buttons">
							<input id="ok-details" type="button" value="OK" class="ctr" />
						</div>
					</div>					
					<div id="diag-disconnect" class="diag-box">
						<div class="diag-box-win">
							<p>Are you sure you would like to disconnect from this wifi?</p>
							<div class="buttons">
								<input id="no-disconnect" type="button" value="No" />
								<input id="yes-disconnect" type="button" value="Yes" />
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
		<div id="credits">
			<header>
				<h1>About this app...</h1>
			</header>
			<h2></h2>
			<section>
				<p><strong>esp32-wifi-manager</strong>, &copy; 2017-2020, Tony Pottier<br />Licended under the MIT License.</p>
				<p>
					This app would not be possible without the following libraries:
				</p>
				<ul>
					<li>SpinKit, &copy;  2015, Tobias Ahlin. Licensed under the MIT License.</li>
					<li>jQuery, The jQuery Foundation. Licensed under the MIT License.</li>
					<li>cJSON, &copy; 2009-2017, Dave Gamble and cJSON contributors. Licensed under the MIT License.</li>
				</ul>
			</section>
			<div class="buttons">
				<input id="ok-credits" type="button" value="OK" class="ctr" />
			</div>
		</div>
	</body>
<html>
)rawliteral";

const char style_css[] PROGMEM = R"rawliteral(
  body {
    background-color: #eee;
    border: 0;
    margin: 0;
    font: 1.1em tahoma, arial, sans-serif;
}
a {
    color: darkblue;
    transition: color .2s ease-out;
    text-decoration: none
}
a:hover {
    color: red;
}
input {
    display: none;
    font: 1.1em tahoma, arial, sans-serif;
}
input:focus,
select:focus,
textarea:focus,
button:focus {
    outline: none;
}
input[type="button"] {
    width: 100px;
    padding: 5px;
    text-align: center;
    display: block;
}
p {
    padding: 10px;
}
#credits {
    display: none;
}
#app {} #app-wrap {} #disconnect {
    width: 150px;
}
.diag-box {
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    height: 100%;
    width: 100%;
    display: none;
}
.diag-box-win {
    position: absolute;
    left: 10%;
    width: 80%;
    text-align: center;
    border: 2px outset #888;
    background-color: #fff;
    border-radius: 10px;
    top: 20%;
}
.blur {
    -webkit-filter: blur(2px);
    -moz-filter: blur(2px);
    -ms-filter: blur(2px);
    -o-filter: blur(2px);
    filter: blur(2px);
}
.ape {
    margin-left: 20px;
    padding: 10px 0px 10px 10px;
}
.ape:hover {
    cursor: pointer;
}
.brdb {
    border-bottom: 1px solid #888;
}
header {
    background-color: #fff;
    border-bottom: 1px solid #888;
}
section {
    background-color: #fff;
    border-bottom: 1px solid #888;
    border-top: 1px solid #888;
}
h1 {
    display: block;
    text-align: center;
    margin: 0;
    padding: 15px;
    font-size: 1.4em
}
h2 {
    margin: 0;
    margin-top: 20px;
    padding: 10px;
    text-transform: uppercase;
    color: #888;
    font-size: 1.0em
}
h3 {
    margin: 0;
    text-align: center;
    padding: 20px 0px 20px 0px;
}
.gr {
    color: green;
}
.rd {
    color: red;
}
#wifi-status {
    display: none;
}
#connect {
    display: none;
}
#connect_manual {
    display: none;
}
#manual_ssid {
    border: none;
    width: 80%;
    margin-left: 35px;
    padding: 10px 0px 10px 10px;
    display: block
}
#manual_pwd {
    border: none;
    width: 80%;
    margin-left: 35px;
    padding: 10px 0px 10px 10px;
    display: block
}
#pwd {
    border: none;
    width: 80%;
    margin-left: 35px;
    padding: 10px 0px 10px 10px;
    display: block
}
.buttons {
    padding: 15px;
}
#join {
    float: right;
}
#manual_join {
    float: right;
}
#yes-disconnect {
    display: inline-block;
    margin-left: 20px;
}
#no-disconnect {
    display: inline-block;
}
.ctr {
    margin: 0 auto;
}
.tctr {
    text-align: center;
}
#connect-wait {
    display: none;
}
#connect-success {
    display: none;
}
#connect-fail {
    display: none;
}
#connect-details {
    display: none;
}
.fr {
    float: right;
    margin-right: 20px;
}
.w0 {
    background: url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+Cjxzdmcgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxwYXRoIGQ9Ik0xLDlMMywxMUM3Ljk3LDYuMDMgMTYuMDMsNi4wMyAyMSwxMUwyMyw5QzE2LjkzLDIuOTMgNy4wOCwyLjkzIDEsOVoiIHN0eWxlPSJmaWxsOiBibGFjazsiLz4KPHBhdGggZD0iTTUsMTNMNywxNUM5Ljc2LDEyLjI0IDE0LjI0LDEyLjI0IDE3LDE1TDE5LDEzQzE1LjE0LDkuMTQgOC44Nyw5LjE0IDUsMTNaIiBzdHlsZT0iZmlsbDogYmxhY2s7Ii8+CjxwYXRoIGQ9Ik05LDE3TDEyLDIwTDE1LDE3QzEzLjM1LDE1LjM0IDEwLjY2LDE1LjM0IDksMTdaIiBzdHlsZT0iZmlsbDogYmxhY2s7Ii8+Cjwvc3ZnPgo=') no-repeat right top;
    height: 24px;
    margin-right: 20px;
}
.w1 {
    background:  url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+Cjxzdmcgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxwYXRoIGQ9Ik0xLDlMMywxMUM3Ljk3LDYuMDMgMTYuMDMsNi4wMyAyMSwxMUwyMyw5QzE2LjkzLDIuOTMgNy4wOCwyLjkzIDEsOVoiIHN0eWxlPSJmaWxsOiBncmF5OyIvPgo8cGF0aCBkPSJNNSwxM0w3LDE1QzkuNzYsMTIuMjQgMTQuMjQsMTIuMjQgMTcsMTVMMTksMTNDMTUuMTQsOS4xNCA4Ljg3LDkuMTQgNSwxM1oiIHN0eWxlPSJmaWxsOiBibGFjazsiLz4KPHBhdGggZD0iTTksMTdMMTIsMjBMMTUsMTdDMTMuMzUsMTUuMzQgMTAuNjYsMTUuMzQgOSwxN1oiIHN0eWxlPSJmaWxsOiBibGFjazsiLz4KPC9zdmc+Cg==') no-repeat right top;
    height: 24px;
    margin-right: 20px;
}
.w2 {
    background:  url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+Cjxzdmcgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxwYXRoIGQ9Ik0xLDlMMywxMUM3Ljk3LDYuMDMgMTYuMDMsNi4wMyAyMSwxMUwyMyw5QzE2LjkzLDIuOTMgNy4wOCwyLjkzIDEsOVoiIHN0eWxlPSJmaWxsOiBncmF5OyIvPgo8cGF0aCBkPSJNNSwxM0w3LDE1QzkuNzYsMTIuMjQgMTQuMjQsMTIuMjQgMTcsMTVMMTksMTNDMTUuMTQsOS4xNCA4Ljg3LDkuMTQgNSwxM1oiIHN0eWxlPSJmaWxsOiBncmF5OyIvPgo8cGF0aCBkPSJNOSwxN0wxMiwyMEwxNSwxN0MxMy4zNSwxNS4zNCAxMC42NiwxNS4zNCA5LDE3WiIgc3R5bGU9ImZpbGw6IGJsYWNrOyIvPgo8L3N2Zz4K') no-repeat right top;
    height: 24px;
    margin-right: 20px;
}
.w3 {
    background:  url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+Cjxzdmcgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxwYXRoIGQ9Ik0xLDlMMywxMUM3Ljk3LDYuMDMgMTYuMDMsNi4wMyAyMSwxMUwyMyw5QzE2LjkzLDIuOTMgNy4wOCwyLjkzIDEsOVoiIHN0eWxlPSJmaWxsOiBncmF5OyIvPgo8cGF0aCBkPSJNNSwxM0w3LDE1QzkuNzYsMTIuMjQgMTQuMjQsMTIuMjQgMTcsMTVMMTksMTNDMTUuMTQsOS4xNCA4Ljg3LDkuMTQgNSwxM1oiIHN0eWxlPSJmaWxsOiBncmF5OyIvPgo8cGF0aCBkPSJNOSwxN0wxMiwyMEwxNSwxN0MxMy4zNSwxNS4zNCAxMC42NiwxNS4zNCA5LDE3WiIgc3R5bGU9ImZpbGw6IGdyYXk7Ii8+Cjwvc3ZnPgo=') no-repeat right top;
    height: 24px;
    margin-right: 20px;
}
.pw {
    background:  url('data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iVVRGLTgiIHN0YW5kYWxvbmU9Im5vIj8+CjwhRE9DVFlQRSBzdmcgUFVCTElDICItLy9XM0MvL0RURCBTVkcgMS4xLy9FTiIgImh0dHA6Ly93d3cudzMub3JnL0dyYXBoaWNzL1NWRy8xLjEvRFREL3N2ZzExLmR0ZCI+Cjxzdmcgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiB2ZXJzaW9uPSIxLjEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+CjxwYXRoIHN0eWxlPSJmaWxsOiBibGFjazsiIGQ9Ik0xOCA4aC0xVjZjMC0yLjc2LTIuMjQtNS01LTVTNyAzLjI0IDcgNnYySDZjLTEuMSAwLTIgLjktMiAydjEwYzAgMS4xLjkgMiAyIDJoMTJjMS4xIDAgMi0uOSAyLTJWMTBjMC0xLjEtLjktMi0yLTJ6bS02IDljLTEuMSAwLTItLjktMi0ycy45LTIgMi0yIDIgLjkgMiAyLS45IDItMiAyem0zLjEtOUg4LjlWNmMwLTEuNzEgMS4zOS0zLjEgMy4xLTMuMSAxLjcxIDAgMy4xIDEuMzkgMy4xIDMuMXYyeiI+PC9wYXRoPgo8L3N2Zz4=') no-repeat right top;
    height: 24px;
    margin-right: 30px;
}

.spinner {
    width: 40px;
    height: 40px;
    position: relative;
    margin: 100px auto;
}
.double-bounce1,
.double-bounce2 {
    width: 100%;
    height: 100%;
    border-radius: 50%;
    background-color: #333;
    opacity: 0.6;
    position: absolute;
    top: 0;
    left: 0;
    -webkit-animation: sk-bounce 2.0s infinite ease-in-out;
    animation: sk-bounce 2.0s infinite ease-in-out;
}
.double-bounce2 {
    -webkit-animation-delay: -1.0s;
    animation-delay: -1.0s;
}
@-webkit-keyframes sk-bounce {
    0%, 100% {
        -webkit-transform: scale(0.0)
    }
    50% {
        -webkit-transform: scale(1.0)
    }
}
@keyframes sk-bounce {
    0%, 100% {
        transform: scale(0.0);
        -webkit-transform: scale(0.0);
    }
    50% {
        transform: scale(1.0);
        -webkit-transform: scale(1.0);
    }
}
)rawliteral";

const char code_js[] PROGMEM = R"rawliteral(
const gel = (e) => document.getElementById(e);

const wifi_div = gel("wifi");
const connect_div = gel("connect");
const connect_manual_div = gel("connect_manual");
const connect_wait_div = gel("connect-wait");
const connect_details_div = gel("connect-details");

function docReady(fn) {
  if (
    document.readyState === "complete" ||
    document.readyState === "interactive"
  ) {
    setTimeout(fn, 1);
  } else {
    document.addEventListener("DOMContentLoaded", fn);
  }
}
var selectedSSID = "";
var refreshAPInterval = null;
var checkStatusInterval = null;

function stopCheckStatusInterval() {
  if (checkStatusInterval != null) {
    clearInterval(checkStatusInterval);
    checkStatusInterval = null;
  }
}

function stopRefreshAPInterval() {
  if (refreshAPInterval != null) {
    clearInterval(refreshAPInterval);
    refreshAPInterval = null;
  }
}

function startCheckStatusInterval() {
  checkStatusInterval = setInterval(checkStatus, 950);
}

function startRefreshAPInterval() {
  refreshAPInterval = setInterval(refreshAP, 3800);
}

docReady(async function () {
  gel("wifi-status").addEventListener(
    "click",
    () => {
      wifi_div.style.display = "none";
      document.getElementById("connect-details").style.display = "block";
    },
    false
  );

  gel("manual_add").addEventListener(
    "click",
    (e) => {
      selectedSSID = e.target.innerText;

      gel("ssid-pwd").textContent = selectedSSID;
      wifi_div.style.display = "none";
      connect_manual_div.style.display = "block";
      connect_div.style.display = "none";

      gel("connect-success").display = "none";
      gel("connect-fail").display = "none";
    },
    false
  );

  gel("wifi-list").addEventListener(
    "click",
    (e) => {
      selectedSSID = e.target.innerText;
      gel("ssid-pwd").textContent = selectedSSID;
      connect_div.style.display = "block";
      wifi_div.style.display = "none";
      // init_cancel();
    },
    false
  );

  function cancel() {
    selectedSSID = "";
    connect_div.style.display = "none";
    connect_manual_div.style.display = "none";
    wifi_div.style.display = "block";
  }

  gel("cancel").addEventListener("click", cancel, false);

  gel("manual_cancel").addEventListener("click", cancel, false);

  gel("join").addEventListener("click", performConnect, false);

  gel("manual_join").addEventListener(
    "click",
    (e) => {
      performConnect("manual");
    },
    false
  );

  gel("ok-details").addEventListener(
    "click",
    () => {
      connect_details_div.style.display = "none";
      wifi_div.style.display = "block";
    },
    false
  );

  gel("ok-credits").addEventListener(
    "click",
    () => {
      gel("credits").style.display = "none";
      gel("app").style.display = "block";
    },
    false
  );

  gel("acredits").addEventListener(
    "click",
    () => {
      event.preventDefault();
      gel("app").style.display = "none";
      gel("credits").style.display = "block";
    },
    false
  );

  gel("ok-connect").addEventListener(
    "click",
    () => {
      connect_wait_div.style.display = "none";
      wifi_div.style.display = "block";
    },
    false
  );

  gel("disconnect").addEventListener(
    "click",
    () => {
      gel("diag-disconnect").style.display = "block";
      gel("connect-details-wrap").classList.add("blur");
    },
    false
  );

  gel("no-disconnect").addEventListener(
    "click",
    () => {
      gel("diag-disconnect").style.display = "none";
      gel("connect-details-wrap").classList.remove("blur");
    },
    false
  );

  gel("yes-disconnect").addEventListener("click", async () => {
    stopCheckStatusInterval();
    selectedSSID = "";

    document.getElementById("diag-disconnect").style.display = "none";
    gel("connect-details-wrap").classList.remove("blur");

    await fetch("connect.json", {
      method: "DELETE",
      headers: {
        "Content-Type": "application/json",
      },
      body: { timestamp: Date.now() },
    });

    startCheckStatusInterval();

    connect_details_div.style.display = "none";
    wifi_div.style.display = "block";
  });

  await refreshAP();
  startCheckStatusInterval();
  startRefreshAPInterval();
});

async function performConnect(conntype) {
  stopCheckStatusInterval();

  stopRefreshAPInterval();

  var pwd;
  if (conntype == "manual") {
    selectedSSID = gel("manual_ssid").value;
    pwd = gel("manual_pwd").value;
  } else {
    pwd = gel("pwd").value;
  }
  gel("loading").style.display = "block";
  gel("connect-success").style.display = "none";
  gel("connect-fail").style.display = "none";

  gel("ok-connect").disabled = true;
  gel("ssid-wait").textContent = selectedSSID;
  connect_div.style.display = "none";
  connect_manual_div.style.display = "none";
  connect_wait_div.style.display = "block";

  await fetch("connect.json", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      "X-Custom-ssid": selectedSSID,
      "X-Custom-pwd": pwd,
    },
    body: { timestamp: Date.now() },
  });

  startCheckStatusInterval();
  startRefreshAPInterval();
}

function rssiToIcon(rssi) {
  if (rssi >= -60) {
    return "w0";
  } else if (rssi >= -67) {
    return "w1";
  } else if (rssi >= -75) {
    return "w2";
  } else {
    return "w3";
  }
}

async function refreshAP(url = "ap.json") {
  try {
    var res = await fetch(url);
    var access_points = await res.json();
    if (access_points.length > 0) {
      
      access_points.sort((a, b) => {
        var x = a["rssi"];
        var y = b["rssi"];
        return x < y ? 1 : x > y ? -1 : 0;
      });
      refreshAPHTML(access_points);
    }
  } catch (e) {
    console.info("Access points returned empty from /ap.json!");
  }
}

function refreshAPHTML(data) {
  var h = "";
  data.forEach(function (e, idx, array) {
    let ap_class = idx === array.length - 1 ? "" : " brdb";
    let rssicon = rssiToIcon(e.rssi);
    let auth = e.auth == 0 ? "" : "pw";
    h += `<div class="ape${ap_class}"><div class="${rssicon}"><div class="${auth}">${e.ssid}</div></div></div>\n`;
  });

  gel("wifi-list").innerHTML = h;
}

async function checkStatus(url = "status.json") {
  try {
    var response = await fetch(url);
    var data = await response.json();
    if (data && data.hasOwnProperty("ssid") && data["ssid"] != "") {
      if (data["ssid"] === selectedSSID) {
        
        switch (data["urc"]) {
          case 0:
            console.info("Got connection!");
            document.querySelector(
              "#connected-to div div div span"
            ).textContent = data["ssid"];
            document.querySelector("#connect-details h1").textContent =
              data["ssid"];
            gel("ip").textContent = data["ip"];
            gel("netmask").textContent = data["netmask"];
            gel("gw").textContent = data["gw"];
            gel("wifi-status").style.display = "block";

            
            gel("ok-connect").disabled = false;

            
            gel("loading").style.display = "none";
            gel("connect-success").style.display = "block";
            gel("connect-fail").style.display = "none";
            break;
          case 1:
            console.info("Connection attempt failed!");
            document.querySelector(
              "#connected-to div div div span"
            ).textContent = data["ssid"];
            document.querySelector("#connect-details h1").textContent =
              data["ssid"];
            gel("ip").textContent = "0.0.0.0";
            gel("netmask").textContent = "0.0.0.0";
            gel("gw").textContent = "0.0.0.0";

            
            gel("wifi-status").display = "none";

            
            gel("ok-connect").disabled = false;

            
            gel("loading").display = "none";
            gel("connect-fail").style.display = "block";
            gel("connect-success").style.display = "none";
            break;
        }
      } else if (data.hasOwnProperty("urc") && data["urc"] === 0) {
        console.info("Connection established");
        
        if (
          gel("wifi-status").style.display == "" ||
          gel("wifi-status").style.display == "none"
        ) {
          document.querySelector("#connected-to div div div span").textContent =
            data["ssid"];
          document.querySelector("#connect-details h1").textContent =
            data["ssid"];
          gel("ip").textContent = data["ip"];
          gel("netmask").textContent = data["netmask"];
          gel("gw").textContent = data["gw"];
          gel("wifi-status").style.display = "block";
        }
      }
    } else if (data.hasOwnProperty("urc") && data["urc"] === 2) {
      console.log("Manual disconnect requested...");
      if (gel("wifi-status").style.display == "block") {
        gel("wifi-status").style.display = "none";
      }
    }
  } catch (e) {
    console.info("Was not able to fetch /status.json");
  }
}
)rawliteral";

// const char ap_json[] PROGMEM = R"rawliteral(
// [
// {"ssid":"Pantum-AP-A6D49F","chan":11,"rssi":-55,"auth":4},
// {"ssid":"a0308","chan":1,"rssi":-56,"auth":3},
// {"ssid":"dlink-D9D8","chan":11,"rssi":-82,"auth":4},
// {"ssid":"Linksys06730","chan":7,"rssi":-85,"auth":3},
// {"ssid":"SINGTEL-5171","chan":9,"rssi":-88,"auth":4},
// {"ssid":"1126-1","chan":11,"rssi":-89,"auth":4},
// {"ssid":"The Shah 5GHz-2","chan":1,"rssi":-90,"auth":3},
// {"ssid":"SINGTEL-1D28 (2G)","chan":11,"rssi":-91,"auth":3},
// {"ssid":"dlink-F864","chan":1,"rssi":-92,"auth":4},
// {"ssid":"dlink-74F0","chan":1,"rssi":-93,"auth":4}
// ]
// )rawliteral";

const char status_json[] PROGMEM = R"rawliteral(
  {"ssid":"zodmgbbq","ip":"192.168.1.119","netmask":"255.255.255.0","gw":"192.168.1.1","urc":0}
)rawliteral";

const char connect_json[] PROGMEM = R"rawliteral(
<html>
</html>
)rawliteral";
