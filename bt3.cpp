#include <stdio.h>
struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};
int main() {
    struct UserAccount user_list[100];
    struct UserAccount active_list[100];
    struct UserAccount free_list[100];
    int n;
    int i, j;
    int active_count = 0;
    int free_count = 0;
    int downgraded_count = 0;
    int mrr_before = 0;
    int mrr_after = 0;
    int temp;
    struct UserAccount temp_account;
    do {
        printf("Nhap so luong tai khoan (1-100): ");
        scanf("%d", &n);
        if (n < 1 || n > 100) {
            printf("So luong khong hop le, vui long nhap lai!\n");
        }
    } while (n < 1 || n > 100);
    for (i = 0; i < n; i++) {
        printf("\nNhap tai khoan %d:\n", i + 1);
        printf("Account ID: ");
        scanf("%d", &user_list[i].account_id);
        do {
            printf("Plan type (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &user_list[i].plan_type);
            if (user_list[i].plan_type < 0 || user_list[i].plan_type > 2) {
                printf("Plan type khong hop le, vui long nhap lai!\n");
            }
        } while (user_list[i].plan_type < 0 || user_list[i].plan_type > 2);
        printf("Monthly fee: ");
        scanf("%d", &user_list[i].monthly_fee);
        printf("Remaining days: ");
        scanf("%d", &user_list[i].remaining_days);
        printf("Active devices: ");
        scanf("%d", &user_list[i].active_devices);
        if (user_list[i].plan_type > 0 &&
            user_list[i].remaining_days > 0) {
            mrr_before += user_list[i].monthly_fee;
        }
    }
    printf("\n=== DU LIEU BAN DAU ===\n");
    printf("%-10s %-10s %-15s %-15s %-15s\n",
           "ID", "PLAN", "MONTHLY FEE", "REMAIN DAYS", "DEVICES");
    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-15d %-15d %-15d\n",
               user_list[i].account_id,
               user_list[i].plan_type,
               user_list[i].monthly_fee,
               user_list[i].remaining_days,
               user_list[i].active_devices);
    }
    for (i = 0; i < n; i++) {
        if (user_list[i].active_devices <= 0) {
            user_list[i].active_devices = 1;
        }
        if (user_list[i].remaining_days <= 0) {
            if (user_list[i].plan_type > 0) {
                downgraded_count++;
            }
            user_list[i].plan_type = 0;
            user_list[i].monthly_fee = 0;
        } else {
            if (user_list[i].plan_type == 0) {
                user_list[i].monthly_fee = 0;
                if (user_list[i].active_devices > 1) {
                    user_list[i].active_devices = 1;
                }
            } else if (user_list[i].plan_type == 1) {
                user_list[i].monthly_fee = 120000;
                if (user_list[i].active_devices > 2) {
                    user_list[i].active_devices = 2;
                }
            } else if (user_list[i].plan_type == 2) {
                user_list[i].monthly_fee = 300000;
                if (user_list[i].active_devices > 5) {
                    user_list[i].active_devices = 5;
                }
            }
        }
        if (user_list[i].plan_type > 0) {
            active_list[active_count] = user_list[i];
            active_count++;
            mrr_after += user_list[i].monthly_fee;
        } else {
            free_list[free_count] = user_list[i];
            free_count++;
        }
    }
    for (i = 0; i < active_count - 1; i++) {
        for (j = i + 1; j < active_count; j++) {
            if (active_list[i].monthly_fee < active_list[j].monthly_fee) {
                temp_account = active_list[i];
                active_list[i] = active_list[j];
                active_list[j] = temp_account;
            }
        }
    }
    for (i = 0; i < active_count; i++) {
        user_list[i] = active_list[i];
    }
    for (i = 0; i < free_count; i++) {
        user_list[active_count + i] = free_list[i];
    }
    printf("\n=== KET QUA SAU KIEM TOAN ===\n");
    printf("%-10s %-10s %-15s %-15s %-15s\n",
           "ID", "PLAN", "MONTHLY FEE", "REMAIN DAYS", "DEVICES");
    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-15d %-15d %-15d\n",
               user_list[i].account_id,
               user_list[i].plan_type,
               user_list[i].monthly_fee,
               user_list[i].remaining_days,
               user_list[i].active_devices);
    }
    printf("\n=== BAO CAO MRR ===\n");
    printf("MRR truoc kiem toan: %d VND\n", mrr_before);
    printf("MRR sau kiem toan:   %d VND\n", mrr_after);
    if (mrr_after > mrr_before) {
        temp = mrr_after - mrr_before;
        printf("Chenh lech MRR: +%d VND\n", temp);
    } else {
        temp = mrr_before - mrr_after;
        printf("Chenh lech MRR: -%d VND\n", temp);
    }
    printf("So tai khoan bi ha cap: %d\n", downgraded_count);
    return 0;
}
