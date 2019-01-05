using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WpfDemo.Models;

namespace WpfDemo.ModelViews
{
    public class MainViewModel
    {
        public ObservableCollection<Person> PersonsList { get; set; }

        public MainViewModel()
        {
            PersonsList = new ObservableCollection<Person>();
            PersonsList.Add(new Person() { Name = "Zbyszek Nastalski", Age = 38 });
            PersonsList.Add(new Person() { Name = "Ania Drozd", Age = 37 });
            PersonsList.Add(new Person() { Name = "Kelvin Klein", Age = 45 });
        }

    }
}
