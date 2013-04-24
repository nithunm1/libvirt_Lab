/* C Program to implement API using Libvirt */

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,choice,choice_id,num_domains;
    int *active_domains;
    virConnectPtr conn;
    virDomainPtr vdp;

    conn = virConnectOpen("xen:///");

    if (conn == NULL) {
        fprintf(stderr, "Error opening connection to XEN:///  \n");
        return 1;
    }
    else
    {

		//For finding Active Devices
        num_domains=virConnectNumOfDomains(conn);
        active_domanins=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains);

        printf("Active domain IDs : \n");
        for (i = 0 ; i < num_domains ; i++) {
            printf("  %d\n", active_domains[i]);
        }
        free(active_domains);

        while(1)
        {
            
            printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit ");
            scanf("%d",&choice);

            printf("\n Please Insert the Active Domian ID ");
            scanf("%d",&choice_id);
  
            vdp=virDomainLookupById(conn,choice_id);
        
            switch(choice)
            {
                case 1:/* Start */
		       val=virDomainCreate(vdp);
                       if(val==0)      
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 2:/* Suspend */
		       val=virDomainSuspend(vdp);
                       if(val==0)
                           printf("Success");
                       else
                           printf("Failed");   
                       break;
                case 3:/* Resume */ 
		        val=virDomainResume(vdp);
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;

                case 4: /* stop */
						val=virDomainStop(vdp);
                        if(val==0)                     
                            printf("Success");
                        else
                            printf("Failed");   
                        break;
                default:exit(1);
            }
        }
        virConnectClose(conn);
    }
}

