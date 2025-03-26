using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace gui
{
    class UDP
    {
        private string serverIP = "127.0.0.1";
        private int port = 9999;
        private UdpClient serverShell;

        private string initComm = "init";

        public UDP()
        {
            serverShell = new UdpClient();
        }

        public void SetConnection(string server, int port)
        {
            this.serverIP = server;
            this.port = port;
        }

        public string Init()
        {
            try
            {
                serverShell.Connect(this.serverIP, port);
            }
            catch(SocketException)
            {
                MessageBox.Show("소켓에 액세스할 때 오류가 발생했습니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
            catch(ArgumentNullException)
            {
                MessageBox.Show("Endpoint가 null입니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
            catch(ObjectDisposedException)
            {
                MessageBox.Show("Shell과의 연결이 끊어졌습니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
            Send(initComm);
            string initData = Receive();
            return initData;
        }

        public void Send(string msg)
        {
            Byte[] sendBytes = Encoding.ASCII.GetBytes(msg);
            try
            {
                serverShell.Send(sendBytes, sendBytes.Length);
            }
            catch (SocketException)
            {
                MessageBox.Show("Socket Connection이 되지 않았습니다.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        public string Receive()
        {
            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Parse(this.serverIP), 0);

            int euckrCodePage = 51949;  // euc-kr 코드 번호
            System.Text.Encoding.RegisterProvider(System.Text.CodePagesEncodingProvider.Instance);

            try
            {
                Byte[] receiveBytes = serverShell.Receive(ref RemoteIpEndPoint);
                string receiveString = Encoding.GetEncoding(euckrCodePage).GetString(receiveBytes);
                return receiveString;
            }
            catch (SocketException)
            {
                MessageBox.Show("소켓에 액세스할 때 오류가 발생했습니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
            catch (ArgumentNullException)
            {
                MessageBox.Show("Endpoint가 null입니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
            catch (ObjectDisposedException)
            {
                MessageBox.Show("Shell과의 연결이 끊어졌습니다.\n프로그램을 재실행해주세요.", "오류", MessageBoxButton.OK, MessageBoxImage.Error);
                return "";
            }
        }
    }
}
