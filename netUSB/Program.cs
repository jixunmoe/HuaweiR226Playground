using System.Text;
using LibUsbDotNet;
using LibUsbDotNet.Main;

namespace uk.jixun
{
    internal class HuaweiR226ActivateRNDIS
    {
        public static DateTime lastEventDate = DateTime.Now;
        public static UsbDevice device;


        private static UsbDevice findById(int vid, int pid)
        {
            var something = UsbDevice.AllDevices.Find(deviceReg => deviceReg.Vid == vid && deviceReg.Pid == pid && deviceReg.Device != null);
            return something?.Device;
        }

        public static void Main(string[] args)
        {
            ErrorCode ec = ErrorCode.None;

            try
            {
                // Find and open the usb device.
                device = findById(0x12D1, 0x1F07);

                // If the device is open and ready
                if (device == null) throw new Exception("Device Not Found.");


                // If this is a "whole" usb device (libusb-win32, linux libusb-1.0)
                // it exposes an IUsbDevice interface. If not (WinUSB) the 
                // 'wholeUsbDevice' variable will be null indicating this is 
                // an interface of a device; it does not require or support 
                // configuration and interface selection.
                IUsbDevice wholeUsbDevice = device as IUsbDevice;
                if (!ReferenceEquals(wholeUsbDevice, null))
                {
                    // This is a "whole" USB device. Before it can be used, 
                    // the desired configuration and interface must be selected.

                    // Select config #1
                    wholeUsbDevice.SetConfiguration(1);

                    // Claim interface #0.
                    wholeUsbDevice.ClaimInterface(0);
                }

                // open read endpoint 1.
                UsbEndpointReader reader = device.OpenEndpointReader(ReadEndpointID.Ep01);

                // open write endpoint 1.
                UsbEndpointWriter writer = device.OpenEndpointWriter(WriteEndpointID.Ep01);

                // Remove the exepath/startup filename text from the begining of the CommandLine.
                byte[] payload = {
                    0x55, 0x53, 0x42, 0x43, 0x12, 0x34, 0x56, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
                    0x06, 0x20, 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                };


                reader.DataReceived += (OnRxEndPointData);
                reader.DataReceivedEnabled = true;

                int bytesWritten;
                ec = writer.Write(payload, 2000, out bytesWritten);
                if (ec != ErrorCode.None) throw new Exception(UsbDevice.LastErrorString);

                lastEventDate = DateTime.Now;
                while ((DateTime.Now - lastEventDate).TotalMilliseconds < 100)
                {
                }

                // Always disable and unhook event when done.
                reader.DataReceivedEnabled = false;
                reader.DataReceived -= (OnRxEndPointData);

                Console.WriteLine("\nDone!\n");
                
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine((ec != ErrorCode.None ? ec + ":" : String.Empty) + ex.Message);
            }
            finally
            {
                if (device != null)
                {
                    if (device.IsOpen)
                    {
                        // If this is a "whole" usb device (libusb-win32, linux libusb-1.0)
                        // it exposes an IUsbDevice interface. If not (WinUSB) the 
                        // 'wholeUsbDevice' variable will be null indicating this is 
                        // an interface of a device; it does not require or support 
                        // configuration and interface selection.
                        IUsbDevice wholeUsbDevice = device as IUsbDevice;
                        if (!ReferenceEquals(wholeUsbDevice, null))
                        {
                            // Release interface #0.
                            wholeUsbDevice.ReleaseInterface(0);
                        }
                        device.Close();
                    }
                }
                device = null;

                // Free usb resources
                UsbDevice.Exit();
            }
        }

        private static void OnRxEndPointData(object sender, EndpointDataEventArgs e)
        {
            lastEventDate = DateTime.Now;
            Console.Write(Encoding.Default.GetString(e.Buffer, 0, e.Count));
        }
    }
}