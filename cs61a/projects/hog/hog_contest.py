import hog
def final_strategy(socre,opponent_score):
    score_copy = score
    max,i,tag = 0,0,1
    while i <= 10:
        now = hog.sus_points(hog.simple_update(i,score,opponent_score))
        if now >= max:
            max = now
            tag = i
        i += 1
    zero_turn = hog.sus_points(hog.simple_update(0,score,opponent_score))
    if zero_turn >= max:
        max = zero_turn 
        tag = 0
    return tag
        
        
             

