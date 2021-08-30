/*
Sample data:
Temperature = 27.03 °F
Humidity    = 56.49 %
Pressure    = 97.51 psi
Illuminance = 40.00 lx
*/

function decodeUplink(input) {
    var sensorData = [];
    var floatSize = 4; // Size of a float in bytes
    var buffer = new ArrayBuffer(input.bytes.length);
    var dataView = new DataView(buffer);
    input.bytes.forEach(function (value, index) {
      dataView.setUint8(index, value);
    });
    
    // Convert the bytes back into float values
    for (var i = 0; i < input.bytes.length; i += floatSize) {
      var floatValue = dataView.getFloat32(i, true);
      sensorData.push(floatValue);
    }

    var data = {
        bytes: input.bytes,
        temperature: sensorData[0] + " °F",
        humidity: sensorData[1] + " %",
        pressure: sensorData[2] + " psi",
        illuminance: sensorData[3] + " lx"
    };

    return {
        data: data,
        warnings: [],
        errors: []
    };
}