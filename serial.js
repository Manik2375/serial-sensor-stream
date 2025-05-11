import { SerialPort } from "serialport";
import { ReadlineParser } from "serialport";

export default function setupSerial(io) {
  const port = new SerialPort({ path: "COM3", baudRate: 9600 }, (err) => {
    if (err) {
      console.error("Error message:" + err.message);
    }
  });

  const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));

  parser.on("data", (data) => {

    const regex = /Temperature:\s(\d+\.\d+)°C\sHumidity:\s(\d+\.\d+)%\sAir\sQuality\s\(Raw\):\s(\d+)\sCigarattes:\s(\d+)/
    const match = data.match(regex);

    if (!match) {
      console.error("The serial port data couldn't be parsed!");
      return;
    }

    const parsedData = {
      temperature: parseFloat(match[1]),
      humidity: parseFloat(match[2]),
      airQuality: parseInt(match[3]),
      cigarattes: parseInt(match[4])
    }

    io.emit("serial-connect", parsedData);
  });

  port.on("close", () => {
    io.emit("serial-disconnect", "Serial Port is closed, the USB device may have been disconnected.");
    console.log("Serial Port is closed, the USB device may have been disconnected.")
  });

  let state = true;
  return function () {
    port.write(state ? "f" : "t");
    state = !state;
  };
}
