using GemStore.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace GemStore.Controllers
{
    public class ProductsController : ApiController
    {
        Product[] products = new Product[] 
        {
            new Product() { 
                name = "Azurite", 
                description="Some gems have hidden qualities beyond their luster, beyond their shine... Azurite is one of those gems.",
                shine = 8,
                price = 110.50, 
                rarity = 7,
                color = "#CCC",
                faces = 14,
                images = new List<string> { "images/gem.png"},
                
                reviews = new List<Review> {
                    new Review() { stars=5, body="I love this gem!", author="joe@example.org" }
                },
            },
 
            new Product() { 
                name = "Bloodstone", 
                description="Origin of the Bloodstone is unknown, hence its low value. It has a very high shine and 12 sides, however.",
                shine = 9,
                price = 22.90, 
                rarity = 6,
                color = "#EEE",
                faces = 12,
                images = new List<string> { "images/gem.png"},
                
                reviews = new List<Review> {
                    new Review() { stars=3, body="I think this gem was just OK, could honestly use more shine, IMO.", author="JimmyDean@example.org" },
                    new Review() { stars=4, body="gemsRock@example.org", author="gemsRock@example.org" }
                },
            },

            new Product() { 
                name = "Zircon", 
                description="Zircon is our most coveted and sought after gem. You will pay much to be the proud owner of this gorgeous and high shine gem.",
                shine = 70,
                price = 1100, 
                rarity = 2,
                color = "#000",
                faces = 6,
                images = new List<string> { "images/gem.png"},
                
                reviews = new List<Review> {
                    new Review() { stars=1, body="This gem is WAY too expensive for its rarity value.", author="turtleguyy@example.org" },
                    new Review() { stars=1, body="BBW: High Shine != High Quality.", author="LouisW407@example.org" },
                    new Review() { stars=1, body="Don't waste your rubles!", author="nat@example.org"}
                },
            },
            
        };

        public IEnumerable<Product> GetAllProducts()
        {
            return products;
        }
        
        /*
        public IHttpActionResult GetProduct(int id)
        {
            var product = products.FirstOrDefault(p => p.Id == id);
            if(product == null)
            {
                return NotFound();
            }

            return Ok(product);

        }
         */ 

       

       
    }
}
