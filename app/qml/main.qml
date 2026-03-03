import QtQuick
import QtQuick.Controls

Window {
    width: 800
    height: 480
    visible: true
    title: "SimVital - Patient Monitor"
    color: "#1e1e1e"

    // 1. THE HISTORY: A JavaScript array to hold our data points
    property var ecgHistory: []
    property int maxPoints: 400 // How many data points fit on the screen at once

    // 2. THE BRIDGE: Listen directly to the C++ controller's signals
    Connections {
        target: ecgController
        function onEcgValChanged(recentEcgVal) {
            // Push the new value to the end of our array
            ecgHistory.push(recentEcgVal)
            
            // If the array gets too long, chop off the oldest data point (creates a scrolling effect)
            if (ecgHistory.length > maxPoints) {
                ecgHistory.shift()
            }
            
            // Tell the Canvas it needs to redraw itself immediately
            ecgCanvas.requestPaint()
        }
    }

    Column {
        anchors.fill: parent
        spacing: 20

        // 3. THE DRAWING BOARD
        Canvas {
            id: ecgCanvas
            width: parent.width
            height: 350
            
            onPaint: {
                var ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);

                // --- 1. THE MINOR GRID (Faint background) ---
                var minorStep = 10; // 10 pixels per small square
                ctx.beginPath();
                ctx.strokeStyle = "#0f2b0f"; // Very dark, faint green
                ctx.lineWidth = 1;

                // Vertical minor lines
                for (var x = 0; x <= width; x += minorStep) {
                    ctx.moveTo(x, 0);
                    ctx.lineTo(x, height);
                }
                // Horizontal minor lines
                for (var y = 0; y <= height; y += minorStep) {
                    ctx.moveTo(0, y);
                    ctx.lineTo(width, y);
                }
                ctx.stroke(); // Physically draw all minor lines at once


                // --- 2. THE MAJOR GRID (Slightly brighter/thicker) ---
                var majorStep = 50; // 50 pixels per large square (5 minor squares)
                ctx.beginPath();
                ctx.strokeStyle = "#1a4d1a"; // Slightly brighter green
                ctx.lineWidth = 1.5;

                // Vertical major lines
                for (var x = 0; x <= width; x += majorStep) {
                    ctx.moveTo(x, 0);
                    ctx.lineTo(x, height);
                }
                // Horizontal major lines
                for (var y = 0; y <= height; y += majorStep) {
                    ctx.moveTo(0, y);
                    ctx.lineTo(width, y);
                }
                ctx.stroke(); // Physically draw all major lines at once
                
                ctx.strokeStyle = "#00ff00";
                ctx.lineWidth = 2;
                ctx.lineJoin = "round";
                
                ctx.beginPath();
                
                var xStep = width / maxPoints;
                
                // 1. Find the exact vertical center of the canvas
                var centerY = height / 2;
                
                // 2. Set the expected baseline (MIT-BIH is usually 1024, sometimes 0)
                var baseline = 1024; 
                
                // 3. Set a scale factor (Higher number = shorter waveform)
                var gain = 0.8; 
                
                for (var i = 0; i < ecgHistory.length; i++) {
                    var x = i * xStep;
                    
                    // --- THE NEW SCALING MATH ---
                    // Subtract the baseline first, then scale it, then apply it to the center
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

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Button {
                text: "Start"
                font.pixelSize: 20
                onClicked: ecgController.start()
            }

            Button {
                text: "Stop"
                font.pixelSize: 20
                onClicked: ecgController.stop()
            }
        }
    }
}