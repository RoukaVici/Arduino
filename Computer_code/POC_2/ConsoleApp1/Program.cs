using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;



namespace ConsoleApp1
{
    class Program
    {

        static void send(SerialPort port, byte num, byte intensity)
        {
            Byte[] pload = { num, intensity };
            port.Write(pload, 0, 2);
        }

        static void takeInput(SerialPort port)
        {
            // Intensity will go up and down with arrow keys
            byte intensity = 255;
            // How much the arrow keys affect the value
            const byte step = 5;
            bool QisOn = false;
            bool WisOn = false;

            Console.WriteLine("Press ESC to stop");
            while (true)
            {
                while (!Console.KeyAvailable)
                {
                    ConsoleKeyInfo k = Console.ReadKey();
                    if (k.Key == ConsoleKey.Escape)
                        return;
                    switch (k.Key)
                    {
                        case ConsoleKey.Q:
                            send(port, 0, intensity);
                            QisOn = true;
                            break;
                        case ConsoleKey.W:
                            send(port, 1, intensity);
                            WisOn = true;
                            break;
                        case ConsoleKey.A:
                            QisOn = false;
                            send(port, 0, 0);
                            break;
                        case ConsoleKey.S:
                            QisOn = false;
                            send(port, 1, 0);
                            break;
                        case ConsoleKey.UpArrow:
                            if (intensity + step <= 255)
                                intensity += step;
                            if (QisOn) send(port, 0, intensity);
                            if (WisOn) send(port, 1, intensity);
                            break;
                        case ConsoleKey.DownArrow:
                            if (intensity-step >= 0)
                                intensity -= step;
                            if (QisOn) send(port, 0, intensity);
                            if (WisOn) send(port, 1, intensity);
                            break;
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Opening port...");
            // Select the right port
            SerialPort port = new SerialPort("COM5");
            // Attempt to open it
            port.Open();

            if (port.IsOpen)
            {
                Console.WriteLine("Done!");
                // Port is open, take user input
                Program.takeInput(port);
            }
            else
            {
                Console.WriteLine("Could not open port");
            }
            port.Close();
        }
    }
}
