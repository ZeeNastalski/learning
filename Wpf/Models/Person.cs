using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using WpfDemo.Annotations;

namespace WpfDemo.Models
{
    public class Person : INotifyPropertyChanged
    {
        private string name;
        private int age;


        public string Name
        {
            get => name;
            set
            {
                this.name = value;
                OnPropertyChanged();
            }

        }

        public int Age
        {
            get => age;
            set
            {
                age = value;
                OnPropertyChanged();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
