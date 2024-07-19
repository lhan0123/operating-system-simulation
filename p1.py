-*- coding: utf-8 -*-
"""
Created on Tue Apr 14 00:42:12 2020

@author: USER1
"""

import threading
import time
import multiprocessing as mp


class SORT:
    def __init__( self ):
        self.processID_list = []
        self.tmpID_list = [] 
    
    def CopyPorcessListToTmpList( self ):
        self.tmpID_list.clear()
        self.tmpID_list = self.processID_list.copy()
        
    def ReadFile( self ):
        index = 0 
        fileName = input( "Input File Name: " )
        fp = open(fileName, "r")
        fp.readline()
        inputRaw = fp.readline()
        lineList = inputRaw.split()
        for j in lineList:
            if ( index == 10 ): break
            self.processID_list.append( int(j) )
            index += 1
        fp.close()
        
    def BubbleSort( self, start, end ):
        n = end + 1
        for i in range( start, n - 1 ):
            for j in range( i + 1, n ):
                if (  self.tmpID_list[i] > self.tmpID_list[j] ):
                    self.tmpID_list[i], self.tmpID_list[j] = self.tmpID_list[j], self.tmpID_list[i]
        return self.tmpID_list[start:end+1]

   
    def Merge( self, start, mid, end ):
        n1 = mid-start
        n2 = end - mid + 1
        
        L = []
        R = []
        
        L.extend( self.tmpID_list[start:mid])
        R.extend( self.tmpID_list[mid:end+1])

        i = j = 0
        for k in range( start, end+1 ):
            if i < n1 and j < n2:
                if L[i] <= R[j]:
                    self.tmpID_list[k] = L[i]
                    i += 1
                else:
                    self.tmpID_list[k] = R[j]
                    j += 1
            elif i < n1 and j >= n2:
                self.tmpID_list[k] = L[i]
                i += 1
            else:
                self.tmpID_list[k] = R[j]
                j += 1
        return [start, end, self.tmpID_list[start:end+1]]

        
    def case4_Bubble_Merge_Sort( self, part, q ):
        tmpID_list_length = len(self.tmpID_list)
        time_to_change_bubble_sort_data_total = part - tmpID_list_length % part
        bubble_sort_data_total = tmpID_list_length // part
        
        start_merge_sort_num = []
        tmp_start_merge_sort_num = []
        
        i = 0
        start = end = -1
        while i != part :
            if ( i == time_to_change_bubble_sort_data_total ): bubble_sort_data_total = bubble_sort_data_total + 1
            start = end + 1
            start_merge_sort_num.append(start)
            end = start + bubble_sort_data_total - 1
            if end > tmpID_list_length-1:
               end = tmpID_list_length-1
            self.BubbleSort( start, end )
            i = i + 1
            
        while ( part != 1 ):
            
            level_merge_total = part // 2
            i = 0
            start_list_length = len(start_merge_sort_num)
            
            while level_merge_total != 0:
                start = start_merge_sort_num[i]
                tmp_start_merge_sort_num.append(start)
                if ( ( i + 2) >= start_list_length  ):
                      end = tmpID_list_length-1
                else:
                      end = start_merge_sort_num[i+2]-1
                mid = start_merge_sort_num[i+1]
                level_merge_total = level_merge_total -1
                part = part - 1
                self.Merge(start, mid, end) 
                i = i + 2
                
            if ( i < start_list_length): 
                    tmp_start_merge_sort_num.append( start_merge_sort_num[i] )
            start_merge_sort_num.clear()
            start_merge_sort_num.extend( tmp_start_merge_sort_num )
            tmp_start_merge_sort_num.clear()  
        q.put(self.tmpID_list)
        
        
if __name__ == "__main__" :     

    s = SORT()
    s.ReadFile()
    
    case = int(input( "Input Command: " ))
    while ( case != 0 ):
        if ( case == 1 ):
            s.CopyPorcessListToTmpList()
            start = time.time()
            s.BubbleSort( 0, len(s.tmpID_list)-1)
            end = time.time()
            with open("result_1.txt","w") as f:
                for num in s.tmpID_list:
                    f.write(str(num) + " ")
                a = float(end-start) / 60
                msg = '%.20f' %a
                print( "performance: ", msg)
                f.write("\nperformance: " + msg) 
            
            
        elif ( case == 2 ):
            s.CopyPorcessListToTmpList()
            tmpID_list_length = len(s.tmpID_list)
            part = int( input( "Input Partition: "))
            
            time_to_change_bubble_sort_data_total = part - tmpID_list_length % part
            bubble_sort_data_total = tmpID_list_length // part
            
            threads_list = []
            start_merge_sort_num = []
            tmp_start_merge_sort_num = []
            start_bubble_time = time.time()
            i = 0
            start = end = -1
            while i != part:
               if ( i == time_to_change_bubble_sort_data_total ): bubble_sort_data_total = bubble_sort_data_total + 1
               start = end + 1
               start_merge_sort_num.append(start)
               end = start + bubble_sort_data_total - 1
               if end > tmpID_list_length-1:
                    end = tmpID_list_length-1
               threads =  threading.Thread(target = s.BubbleSort, args = (start, end))
               threads.start()
               threads_list.append(threads)
               i = i + 1   
            
            for i in range(part):
                threads_list[i].join()
            
            end_bubble_time = time.time()
            threads_list.clear()

            
            start_merge_time = time.time()
            while ( part != 1 ):
                
                level_merge_total = part // 2
                tmp_level_merge_total = level_merge_total
                i = 0
                start_list_length = len(start_merge_sort_num)
                while  level_merge_total != 0:
                  start = start_merge_sort_num[i]
                  tmp_start_merge_sort_num.append(start)             
                  if ( ( i + 2) >= start_list_length  ):
                      end = tmpID_list_length-1
                  else:
                      end = start_merge_sort_num[i+2]-1
                  mid = start_merge_sort_num[i+1]
                  level_merge_total = level_merge_total - 1
                  part = part - 1
                  threads = threading.Thread(target = s.Merge, args = ( start, mid, end ))
                  threads.start()
                  threads_list.append(threads)
                  i = i + 2
                  
                for j in range( tmp_level_merge_total ):
                    threads_list[j].join()
                
                if ( i < len(start_merge_sort_num)): 
                    tmp_start_merge_sort_num.append( start_merge_sort_num[i] )
                threads_list.clear()
                start_merge_sort_num.clear()
                start_merge_sort_num.extend( tmp_start_merge_sort_num )
                tmp_start_merge_sort_num.clear()   
            end_merge_time = time.time()

            with open("result_2.txt","w") as f:
                for num in s.tmpID_list:
                    f.write(str(num) + " ")
                comput_time = float(((end_bubble_time - start_bubble_time) + (end_merge_time - start_merge_time))/ 60)
                msg = '%.20f' %comput_time
                f.write("\nperformance" + msg)
                print( "performance: ", msg)
            
        elif ( case == 3 ):     
            s.CopyPorcessListToTmpList()
            tmpID_list_length = len(s.tmpID_list)
            part = int( input( "Input Partition: "))
            pool = mp.Pool(processes=part)
            
            time_to_change_bubble_sort_data_total = part - tmpID_list_length % part
            bubble_sort_data_total = tmpID_list_length // part
            
            processes_list = []
            start_merge_sort_num = []
            tmp_start_merge_sort_num = []
            
            start_bubble_time = time.time()
            i = 0
            start = end = -1
            while i != part:
                if ( i == time_to_change_bubble_sort_data_total ): bubble_sort_data_total = bubble_sort_data_total + 1
                start = end + 1
                start_merge_sort_num.append(start)
                end = start + bubble_sort_data_total - 1
                if end > tmpID_list_length-1:
                    end = tmpID_list_length-1
                process_result = pool.apply_async( s.BubbleSort ,( start, end ))
                processes_list.append(process_result)
                i = i + 1
                
            merge_sort_data_list = []
            for result in processes_list:
                merge_sort_data_list.extend(result.get())
                
            pool.close()
            pool.join()
            end_bubble_time = time.time()
            
            s.tmpID_list.clear()
            processes_list.clear()
            s.tmpID_list = merge_sort_data_list
            
            start_merge_time = time.time()
            
            while ( part != 1 ):
            
              level_merge_total = part // 2
              tmp_level_merge_total = level_merge_total
              i = 0 
              start_list_length = len(start_merge_sort_num)
              
              pool = mp.Pool(level_merge_total)
              while  level_merge_total != 0:                 
                  start = start_merge_sort_num[i]
                  tmp_start_merge_sort_num.append(start)             
                  if ( ( i + 2) >= start_list_length  ):
                      end = tmpID_list_length-1
                  else:
                      end = start_merge_sort_num[i+2]-1
                  mid = start_merge_sort_num[i+1]
                  level_merge_total = level_merge_total - 1
                  part = part - 1
                  process_result = pool.apply_async( s.Merge ,( start, mid, end ))
                  processes_list.append(process_result)
                  i = i + 2
                  
              for result in processes_list:
                  result_data = result.get()
                  s.tmpID_list[result_data[0]:result_data[1]+1] = result_data[2]
                  
              pool.close()
              pool.join()
                       
              if ( i < len(start_merge_sort_num)): 
                    tmp_start_merge_sort_num.append( start_merge_sort_num[i] )
              
              processes_list.clear()
              start_merge_sort_num.clear()
              start_merge_sort_num.extend( tmp_start_merge_sort_num )
              tmp_start_merge_sort_num.clear()   
              
            end_merge_time = time.time()
           
            with open("result_3.txt","w") as f:
                for num in s.tmpID_list:
                    f.write(str(num) + " ")        
                comput_time = float(((end_bubble_time - start_bubble_time) + (end_merge_time - start_merge_time))/ 60)
                msg = '%.20f' %comput_time
                f.write("\nperformance" + msg)
                print( "performance: ", msg)
  
        elif ( case == 4 ):
            q = mp.Queue()
            s.CopyPorcessListToTmpList()
            part = int( input( "Input Partition: "))

            t_start = time.time()
            process = mp.Process( target=s.case4_Bubble_Merge_Sort, args = ( part, q ) )
            process.start()
            tmp_list = q.get()
            process.join()
            t_end = time.time()
            
            with open("result_4.txt","w") as f:
                for num in tmp_list:
                    f.write(str(num) + " ")
                comput_time = float(t_end-t_start) / 60
                msg = '%.20f' %comput_time
                print( "performance: ", msg)
                f.write("\nperformance: " + msg)         
        else: break
        
        case = int(input( "Input Command: " ))
    print(  "Program Exist..." )
