import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

    property var ecgHistory: []
    property int maxPoints: 400 

    Connections {
        target: ecgController
        function onEcgValChanged(recentEcgVal) {
            ecgHistory.push(recentEcgVal)
            
            if (ecgHistory.length > maxPoints) {
                ecgHistory.shift()
            }
            
            ecgCanvas.requestPaint()
        }
    }

    property var spo2History: []

    Connections {
        target: spo2WaveController
        function onWaveValChanged(spO2Val) {
            spo2History.push(spO2Val)

            if (spo2History.length > maxPoints) {
                spo2History.shift()
            }

            spo2Canvas.requestPaint()
        }
    }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 15

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 30

                Text {
                    id: clockDisplay
                    text: new Date().toLocaleDateString(Qt.locale(), Locale.ShortFormat) + "   " + new Date().toLocaleTimeString(Qt.locale(), Locale.ShortFormat)
                    color: "#a0a0a0"
                    font.pixelSize: 16

                    Timer {
                        interval: 1000 
                        running: true
                        repeat: true
                        onTriggered: {
                            var now = new Date()
                            clockDisplay.text = now.toLocaleDateString(Qt.locale(), Locale.ShortFormat) + "   " + now.toLocaleTimeString(Qt.locale(), Locale.ShortFormat)
                        }
                    }
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "PLACEHOLDER DATE AND TIME"
                    color: "#a0a0a0"
                    font.pixelSize: 16
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 20

                ColumnLayout {
                    Layout.preferredWidth: 550
                    Layout.fillHeight: true
                    spacing: 15

                    Canvas {
                        id: ecgCanvas
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        onPaint: {
                            var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);

                            var minorStep = 10; 
                            ctx.beginPath();
                            ctx.strokeStyle = "#0f2b0f"; 
                            ctx.lineWidth = 1;

                            for (var x = 0; x <= width; x += minorStep) {
                                ctx.moveTo(x, 0);
                                ctx.lineTo(x, height);
                            }
                            for (var y = 0; y <= height; y += minorStep) {
                                ctx.moveTo(0, y);
                                ctx.lineTo(width, y);
                            }
                            ctx.stroke(); 

                            var majorStep = 50; 
                            ctx.beginPath();
                            ctx.strokeStyle = "#1a4d1a"; 
                            ctx.lineWidth = 1.5;

                            for (var x = 0; x <= width; x += majorStep) {
                                ctx.moveTo(x, 0);
                                ctx.lineTo(x, height);
                            }

                            for (var y = 0; y <= height; y += majorStep) {
                                ctx.moveTo(0, y);
                                ctx.lineTo(width, y);
                            }
                            ctx.stroke(); 
                            
                            ctx.strokeStyle = "#00ff00";
                            ctx.lineWidth = 2;
                            ctx.lineJoin = "round";
                            
                            ctx.beginPath();
                            
                            var xStep = width / maxPoints;
                            
                            var centerY = height / 2;
                            
                            var baseline = 1024; 
                            
                            var gain = 0.4; 
                            
                            for (var i = 0; i < ecgHistory.length; i++) {
                                var x = i * xStep;
                                
                                var normalizedValue = (ecgHistory[i] - baseline) * gain;
                                var y = centerY - normalizedValue; 
                                
                                if (i === 0) {
                                    ctx.moveTo(x, y);
                                } else {
                                    ctx.lineTo(x, y);
                                }
                            }   
                            ctx.stroke();
                        }
                    }

                    Canvas {
                        id: spo2Canvas
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        onPaint: {
                            var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);

                            var minorStep = 10; 
                            ctx.beginPath();
                            ctx.strokeStyle = "#0f2b0f"; 
                            ctx.lineWidth = 1;

                            for (var x = 0; x <= width; x += minorStep) {
                                ctx.moveTo(x, 0);
                                ctx.lineTo(x, height);
                            }

                            for (var y = 0; y <= height; y += minorStep) {
                                ctx.moveTo(0, y);
                                ctx.lineTo(width, y);
                            }
                            ctx.stroke(); 


                            var majorStep = 50; 
                            ctx.beginPath();
                            ctx.strokeStyle = "#1a4d1a"; 
                            ctx.lineWidth = 1.5;

                            for (var x = 0; x <= width; x += majorStep) {
                                ctx.moveTo(x, 0);
                                ctx.lineTo(x, height);
                            }

                            for (var y = 0; y <= height; y += majorStep) {
                                ctx.moveTo(0, y);
                                ctx.lineTo(width, y);
                            }
                            ctx.stroke(); 

                            ctx.strokeStyle = "#00bfff";
                            ctx.lineWidth = 2;
                            ctx.lineJoin = "round";
                            
                            ctx.beginPath();
                            
                            var xStep = width / maxPoints;
                            
                            var centerY = height / 2;
                            
                            var baseline = 0; 
                            
                            var gain = 50; 
                            
                            for (var i = 0; i < spo2History.length; i++) {
                                var x = i * xStep;
                                
                                
                                var normalizedValue = (spo2History[i] - baseline) * gain;
                                var y = centerY - normalizedValue; 
                                
                                if (i === 0) {
                                    ctx.moveTo(x, y);
                                } else {
                                    ctx.lineTo(x, y);
                                }
                            }   
                            ctx.stroke();
                        }
                    }
                }

            GridLayout {
                columns: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                columnSpacing: 15
                rowSpacing: 15

                ReadingsBox {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    titleText: "HR"
                    unitText: "bpm"
                    valueText: ecgController ? ecgController.hrVal : "--"
                    valueColor: "#00ff00"
                    isAlarming: ecgController ? ecgController.isAlarming : false
                }

                NibpBox {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    valueText: nibpController ? nibpController.readingVal : "--"
                    lastMeasureTime: nibpController ? nibpController.timeVal : "--"
                    onMeasureClicked: nibpController.startMeasurement()
                    isAlarming: nibpController ? nibpController.isAlarming : false
                }

                ReadingsBox {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    titleText: "SpO2"
                    unitText: "%"
                    valueText: spo2Controller ? (spo2Controller.spO2Val === -1 ? "---" : spo2Controller.spO2Val) : "--"
                    valueColor: "#00bfff"
                    isAlarming: spo2Controller ? spo2Controller.isAlarming : false
                }

                ReadingsBox {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    titleText: "RR"
                    unitText: "rpm"
                    valueText: rrController ? rrController.rrVal : "--"
                    valueColor: "#ffff00"
                    isAlarming: rrController ? rrController.isAlarming : false
                }
            }
        }
    }
}