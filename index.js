import express from "express";
import { createServer } from "http";
import { Server } from "socket.io";
import path from "path";
import { fileURLToPath } from "url";
import setupSerial from "./serial.js";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const server = createServer(app);
const io = new Server(server);

app.use(express.static(path.join(__dirname, "web")));

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "web/index.html"));
});
const serialToggler = setupSerial(io);

server.listen("3000", () => {
  console.log("Server started running at localhost:3000");
});

io.on("connection", (socket) => {
    socket.on("toggle-light", () => {
        serialToggler();
    })
})
