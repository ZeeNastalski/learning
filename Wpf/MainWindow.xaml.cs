using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using WpfDemo.Models;

namespace WpfDemo
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        public MainWindow()
        {
            InitializeComponent();
            this.Title = "Zee's window";
            this.WindowStartupLocation = WindowStartupLocation.CenterScreen;           
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            var personsList = (ObservableCollection<Person>)lvNames.ItemsSource;
            personsList.Add(new Person() { Name = "Steve", Age = 13 });
        }

        private void BtnChange_OnClick(object sender, RoutedEventArgs e)
        {
            var personsList = (ObservableCollection<Person>)lvNames.ItemsSource;
            personsList[0].Name = "Changed";
        }
    }
}
