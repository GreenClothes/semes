using System;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace gui;

/// <summary>
/// Interaction logic for MainWindow.xaml
/// </summary>
public partial class MainWindow : Window
{

    private UDP udp;
    private Dictionary<string, int> classifications = new Dictionary<string, int>() { { "Type", 0 }, { "Engine", 1 }, { "Break", 2 }, { "Steer", 3 } };
    private ComboBox[] selectionBoxes;
    private string[] selectedItems = new string[] {"", "", "", ""};
    

    public MainWindow()
    {
        InitializeComponent();
        Console.WriteLine("Start");
        udp = new UDP();
        selectionBoxes = new ComboBox[] { TypeBox, EngineBox, BreakBox, SteerBox };
        string initData = udp.Init();
        if(initData.Length > 0) SetDropDown(initData);
    }

    private void SetDropDown(string initData)
    {
        string[] data = initData.Split(' ');
        string classification = "";

        foreach(string datum in data)
        {
            if (classifications.ContainsKey(datum))
            {
                classification = datum;
            }
            else
            {
                AddDropDown(classification, datum);
            }
        }
    }

    private void AddDropDown(string classification, string datum)
    {
        if (classification == "") return;

        selectionBoxes[classifications[classification]].Items.Add(datum);
    }

    private void Box_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        string selectedBox = (sender as ComboBox)!.Name.ToString().Replace("Box", "");
        string? selectedItem = (sender as ComboBox)!.SelectedItem.ToString();

        if (selectedBox == null || selectedItem == null) return;
        selectedItems[classifications[selectedBox]] = selectedItem;
    }

    private void TestBtn(object sender, RoutedEventArgs e)
    {
        string sendMsg = "";
        string recvMsg;
        foreach(string selectedItem in selectedItems)
        {
            if(selectedItem == "")
            {
                MessageBox.Show("선택되지 않은 항목이 있습니다.", "미선택", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }
            sendMsg += selectedItem;
            sendMsg += " ";
        }
        udp.Send(sendMsg);
        recvMsg = udp.Receive();

        if(recvMsg.Length > 0) MessageBox.Show(recvMsg, "결과", MessageBoxButton.OK, MessageBoxImage.Information);
    }
}