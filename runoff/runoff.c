#include <cs50.h>
#include <stdio.h>
#include <limits.h>

// 有権者の最大数
#define MAX_VOTERS 100
// 候補者の最大数
#define MAX_CANDIDATES 9

// 投票者番号[i]/投票者iのj番目の選好である候補者のindex
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    // 現在所有している投票数
    int votes;
    // 候補者が選挙から除外されたかどうか
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // 候補者がいない場合
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // 候補者の設定
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // 投票
    for (int i = 0; i < voter_count; i++)
    {

        // 優先順位
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // 無効でない場合、投票を記録
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // 勝者が決まるまで決選投票を続ける
    while (true)
    {
        // 残りの候補者を考慮して票を計算する
        tabulate();

        bool won = print_winner();
        if (won)
        {
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);

        // 引き分けの場合、全員が勝ち
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // 最低投票数の人を除外
        eliminate(min);

        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// 投票が有効な場合は選好を記録
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i ++) 
    {
        if (strcmp(name, candidates[i].name) == 0) 
        {
            preferences[voter][rank] = i;

            return true;
        }
    }
    return false;
}

// 落選しなかった候補者の投票を集計
void tabulate(void)
{
    for (int i = 0; i < voter_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes ++;
                // 次の候補者に移る
                break;
            }
        }
        
    }
    return;
}

bool print_winner(void)
{
    int majority_votes = (voter_count / 2) + (voter_count % 2);

    for (int i = 0; i < candidate_count; i ++)
    {
        if(candidates[i].votes >= majority_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// 残りの候補者が持つ最小票数を返す
int find_min(void)
{
    int min_votes = INT_MAX;

    for (int i = 0; i < candidate_count; i ++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes
        }
    }
    return min_votes;
}

// 候補者間で同点の場合、true
bool is_tie(int min)
{
    // TODO
    return false;
}

// 最下位の候補者を除外
void eliminate(int min)
{
    // TODO
    return;
}
