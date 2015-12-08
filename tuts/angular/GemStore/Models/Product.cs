using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace GemStore.Models
{
    public class Product
    {
        public string name { get; set; }
        public string description { get; set; }
        public int shine { get; set; }
        public double price { get; set; }
        public int rarity { get; set; }
        public string color { get; set; }
        public int faces { get; set; }        
        public List<string> images { get; set; }
        public List<Review> reviews { get; set; }
    
    }
}