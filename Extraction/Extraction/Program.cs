using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;
using ICSharpCode.SharpZipLib.Core;
using ICSharpCode.SharpZipLib.Zip;

namespace Extraction
{
    class Program
    {


        public static void ExtractZip(string zipfile, string destinationPath, string includeMatchPattern = ".*", string excludeMatchPattern = "", Action<double> progressUpdate = null)
        {
            //ZeroLatency.Logger.StandardLogger.LogInfo($"Extracting zip file {zipfile} to {destinationPath}. Include {includeMatchPattern}, Exclude {excludeMatchPattern}");

            long len = new FileInfo(zipfile).Length;

            using (ZipInputStream s = new ZipInputStream(File.OpenRead(zipfile)))
            {
                ZipEntry theEntry;
                while ((theEntry = s.GetNextEntry()) != null)
                {

                    //exclude everything matching exclude pattern if it is specified
                    if (!String.IsNullOrEmpty(excludeMatchPattern) && Regex.IsMatch(theEntry.Name, excludeMatchPattern))
                    {
                        continue;
                    }

                    // exclude everything not matching include pattern
                    if (!Regex.IsMatch(theEntry.Name, includeMatchPattern))
                    {
                        continue;
                    }

                    // update the progrss
                    if (progressUpdate != null)
                    {
                        progressUpdate((double)s.Position / len * 100);
                    }

                    // make sure we are extracting to subdirectory of the destinationPath
                    string directoryName = Path.Combine(destinationPath, Path.GetDirectoryName(theEntry.Name));
                    string fileName = Path.GetFileName(theEntry.Name);

                    // create directory
                    if (directoryName.Length > 0)
                    {
                        Directory.CreateDirectory(directoryName);
                    }

                    if (fileName != String.Empty)
                    {
                        using (FileStream streamWriter = File.Create(Path.Combine(destinationPath, theEntry.Name)))
                        {
                            int size = 2048;
                            byte[] data = new byte[2048];
                            while (true)
                            {
                                size = s.Read(data, 0, data.Length);
                                if (size > 0)
                                {
                                    streamWriter.Write(data, 0, size);
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }











        public static void ExtractZipMT(string zipfile, string destinationPath, int threads)
        {
            // 
            using (ZipInputStream s = new ZipInputStream(File.OpenRead(zipfile)))
            {
                ZipEntry theEntry;
                while ((theEntry = s.GetNextEntry()) != null)
                {
                    var fullPath = Path.Combine(destinationPath, theEntry.Name);
                    var dir = Path.GetDirectoryName(fullPath);

                    //For each directory entry, create one if it doesn't exist
                    if (!Directory.Exists(dir))
                    {
                        Directory.CreateDirectory(Path.Combine(destinationPath, theEntry.Name));
                    }
                }
            }
            
            
            List<Task> tasks = new List<Task>();
            /*
            for (int i = 0; i < threads; i++)
            {                
                Task t = new Task(() => ExtractStreamTask(i, threads, zipfile, destinationPath));
                t.Start();
                tasks.Add(t);
            }

            Task.WaitAll(tasks.ToArray());
            */

            tasks.Add(Task.Run(() => ExtractStreamTask(0, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(1, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(2, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(3, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(4, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(5, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(6, 8, zipfile, destinationPath)));
            tasks.Add(Task.Run(() => ExtractStreamTask(7, 8, zipfile, destinationPath)));

            Task.Run(() => ExtractStreamTask(1, 8, zipfile, destinationPath));
            Task.WaitAll(tasks.ToArray());


            //ExtractStreamTask(0, 1, zipfile, destinationPath);
        }

        private static ZipEntry GetNextFileEntry(ZipInputStream openStream)
        {
            ZipEntry theEntry;
            while (true)
            {
                theEntry = openStream.GetNextEntry();

                // we reached the end
                if (theEntry == null)
                    return null;
                
                if (String.IsNullOrEmpty(theEntry.Name))
                {
                    continue;
                }

                if (theEntry.IsFile)
                {
                    return theEntry;
                }
            }            
        }

        private static void ExtractStreamTask(int taskNo, int taskCount, string zipFile, string destinationPath)
        {
            using (ZipInputStream s = new ZipInputStream(File.OpenRead(zipFile)))
            {
                //fast forward to the file entry number taskNo
                ZipEntry theEntry = null;
                for (int i = 0; i <= taskNo; i++)
                {
                    theEntry = GetNextFileEntry(s);
                }

                if(theEntry == null) return; //we're done 
                

                // at this point the start entry is found and is a file
                while (theEntry != null)
                {
                    //extract entry
                    using (FileStream streamWriter = File.Create(Path.Combine(destinationPath, theEntry.Name)))
                    {
                        int size = 2048;
                        byte[] data = new byte[2048];
                        while (true)
                        {
                            size = s.Read(data, 0, data.Length);
                            if (size > 0)
                            {
                                streamWriter.Write(data, 0, size);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    //fast forward taskCount
                    for (int i = 0; i < taskCount; i++)
                    {
                        theEntry = GetNextFileEntry(s);
                        if (theEntry == null) return;

                    }
                }
            }
        }

        static void Main(string[] args)
        {
            DateTime start = DateTime.Now;

            string zipPath = @"c:\temp\good_file.zip";

            string extractPath = Path.Combine(Path.GetDirectoryName(zipPath), Path.GetFileNameWithoutExtension(zipPath)) ;
            if (Directory.Exists(extractPath))
            {
                Directory.Delete(extractPath, true);
            }

            ExtractZipMT(zipPath, extractPath, 8);

            Console.WriteLine((DateTime.Now - start).TotalSeconds);
            Console.ReadLine(); //13.4 sec
        }
    }
}
